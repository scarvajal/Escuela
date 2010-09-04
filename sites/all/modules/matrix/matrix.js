/**
 * When the DOM is loaded, attach click handlers to the add and edit buttons
 */
$().ready(function() { 
    $('#edit-add-rows, #edit-add-cols, a.matrix-settings-edit').bind('click', matrix_element_form); //bind events to clicks on the edit button and on the add button
    //Drupal.theme.prototype.tableDragChangedWarning = function () {return '';}; //unset the "changes will be saved" message
});

/**
 * Respond to a click event from an add or edit button
 * @param e The event
 */
function matrix_element_form (e) {
  rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
  mode = $("input[name='mode']:checked").val();
  element_id = (this.id.split('-')[3]) ? this.id.split('-')[3] : $("#edit-element-id").val();

  //$('#matrix-'+ rc +'-throbber').html(''); //remove the form elements
  $('#matrix-'+ rc +'-throbber').load(Drupal.settings.basePath + "matrix/throbber",
    {
      'mode': mode,
      'rc': rc,
      'element_type': $('.matrix-'+ rc +'#edit-element-type').val(),
      'element_id': element_id,
      'field_name': $('#edit-info-field-name').val(),
      'field_type': $('#edit-info-field-type').val(),
    },
    function() { //retrieve the element form

    $('.matrix-'+ rc +'#edit-element-type').bind('change', matrix_element_form); //bind the change event to the element-type select box - This will trigger the AJAX call to populate the rest of the fom
    
    $('#edit-save').click(function(){ //when the save button is clicked
      rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
      mode = $("input[name='mode']:checked").val();

      jQuery.getJSON(Drupal.settings.basePath + "matrix/throbber/save", //call the save callback
        {'rc': rc, //rows or columns
         'field_name': $('#edit-info-field-name').val(), //CCK field name
         'element_id': $('.matrix-'+ rc +'#edit-element-id').val(), //index of the row/column
         'element_type': $('.matrix-'+ rc +'#edit-element-type').val(), //pass in all the elements
         'title': $('.matrix-'+ rc +'#edit-title').val(),
         'options': $('.matrix-'+ rc +'#edit-options').val(),
         'size': $('.matrix-'+ rc +'#edit-size').val(),
         'validation': $('.matrix-'+ rc +'#edit-validation').val(),
         'required': $('.matrix-'+ rc +'#edit-required').attr("checked"),
         'calc_method': $('.matrix-'+ rc +'#edit-calc-method').val(),
         'php': $('.matrix-'+ rc +'#edit-php').attr("checked"),
         'mode' : mode,
        },
        function(res) { //after the element is saved rebuild the list of elements and the data form element
          $('#edit-'+ rc +'-list').html(res.list); //this is the list of elements
          $('#edit-'+ rc +'-elements').val(res.data); //this is the serialized data which will eventually go back to the database
          $('#matrix-'+ rc +'-throbber').html(''); //remove the form elements
          $('#matrix-preview').html(res.preview); //show the new preview
          $('a.matrix-settings-edit').bind('click', matrix_element_form); //rebind click events on th edit buttons
          Drupal.attachBehaviors('#edit-'+ rc +'-list'); //attach drupal events such as dragtable
        });
      return false; //this prevents the save button from reloading the form
    });

    $('#edit-cancel').click(function(){ //when the cancel button is clicked
      rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
      $('#matrix-'+ rc +'-throbber').html(''); //just remove the form elements
      return false; //this prevents the cancel button from reloading the form
    });
    
    $('#edit-delete').click(function(){ //when the delete button is clicked
      rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
      mode = $("input[name='mode']:checked").val();

      $('#matrix-'+ rc +'-throbber').load(Drupal.settings.basePath + "matrix/throbber/delete", {'rc': rc, 'mode': mode, 'element_id': $('.matrix-'+ rc +'#edit-element-id').val(), 'field_name': $('#edit-info-field-name').val()}, function() { //fetch the delete button
        $('#edit-delete-confirm').bind('click', function(){ //when the confirm button is pushed
          rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
          mode = $("input[name='mode']:checked").val();

          jQuery.getJSON(Drupal.settings.basePath + "matrix/throbber/delete",
            {'confirm' : 'confirmed',
             'rc' : rc,
             'mode': mode,
             'element_id': $('#edit-element-id').val(),
             'field_name': $('#edit-info-field-name').val()
            },
            function(res){ //delete the element
              $('#edit-'+ rc +'-list').html(res.list); //this is the list of elements
              $('#edit-'+ rc +'-elements').val(res.data); //this is the serialized data which will eventually go back to the database
              $('a.matrix-settings-edit').bind('click', matrix_element_form); //rebind events
              Drupal.attachBehaviors('#edit-'+ rc +'-list'); //reattach drupal originating events
              $('#matrix-'+ rc +'-throbber').html('Component deleted'); //remove the form elements
            });
          return false; //this prevents the delete confirmation button from reloading the form
        });
        
        $('#edit-delete-cancel').bind('click', function(){ //when the cancel button is pushed
          rc = matrix_find_rc(this); //work out if we are dealing with rows or columns (rc)
          $('#matrix-'+ rc +'-throbber').html('');
          return false; //this prevents the cancel from reloading the form
        });
        
      });
      return false; //this prevents the delete button from reloading the form
    });    
    
  });
  return false; //this prevents the add button from reloading the form
};

/**
 * Work out if the element in question is associated with rows or columns
 * This is done by analysing one of the classes attached to the DOM object
 *
 * @param that DOM object of the (clicked) element
 * @return either "rows" or "cols" as appropriate
 */
function matrix_find_rc(that) {
  classes = that.className.split(' ');
  for (i=0; i<classes.length; i++) {
    class_parts = classes[i].split('-');
    if (class_parts[0] == 'matrix' && (class_parts[1] == 'rows' || class_parts[1] == 'cols')) {
      return class_parts[1];
    }
  }
}

/**
 * Move a block in the blocks table from one region to another via select list.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 */
Drupal.behaviors.blockDrag = function(context) {
  var rowsTableDrag = Drupal.tableDrag.matrixrows;
  var colsTableDrag = Drupal.tableDrag.matrixcols;

  if (typeof rowsTableDrag !== 'undefined') {
    rowsTableDrag.onDrop = function() {
      dragObject = this;
      rc = 'rows';
      var orderField = $('div.matrix-settings-rows-order', dragObject.rowObject.element);
      matrix_dragTable(orderField, rc);
    };
  }
  
  colsTableDrag.onDrop = function() {
    dragObject = this;
    var orderField = $('div.matrix-settings-cols-order', dragObject.rowObject.element);
    matrix_dragTable(orderField, rc);
  };
};

/**
 *
 *
 *
 */
function matrix_dragTable(orderField, rc) {
  mode = $("input[name='mode']:checked").val();

  jQuery.getJSON(Drupal.settings.basePath + "matrix/reorder", //call the save callback
        {'rc': rc, //rows or columns
         'field_name': $('#edit-info-field-name').val(), //CCK field name
         'source': orderField[0].id,
         'destination': orderField[0].value,
         'mode': mode
        },
        function(res) { //after the element is saved rebuild the list of elements and the data form element
          $('#edit-'+ rc +'-list').html(res.list); //this is the list of elements
          $('#edit-'+ rc +'-elements').val(res.data); //this is the serialized data which will eventually go back to the database
          $('#matrix-preview').html(res.preview); //show the new preview
          $('a.matrix-settings-edit').bind('click', matrix_element_form); //rebind click events on th edit buttons
          Drupal.attachBehaviors('#edit-'+ rc +'-list'); //reattach drupal based events
        });
}