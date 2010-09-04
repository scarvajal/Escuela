// $Id: og_menu.js,v 1.2 2010/02/09 12:57:00 jide Exp $

/**
 * @file
 * Javascript magic. Shows the eligible menu options when switching groups.
 */

Drupal.behaviors.OGMenu = function() {
  // Initialize variables
  var savedTitle = '';
  var originalParent = $('.menu-title-select').val();
  var inputTitle = $('input[name="menu[link_title]"]');
  var inputDelete = $('input[name="menu[delete]"]');
  var holder = document.createElement('select');
  var disabledOption = $(document.createElement('option'));
  disabledOption.text('--').attr('value', '').attr('class', 'value-none').prependTo('.menu-title-select');

  // Toggle menu alteration
  var toggle = function(values) {
    var title = inputTitle.val()
    var none = true;
    
    // Reset menu form elements
    disabledOption.remove();
    inputDelete.attr('checked', '');
    inputTitle.attr("disabled", '');

    $('.menu-title-select option:not(.value-none)').appendTo(holder);
    $('.menu-title-select').attr("disabled", '');

    // Handle menu link title
    if (savedTitle && !title) {
      inputTitle.val(savedTitle);
      inputTitle.trigger('change'); // Handle vertical tabs
    }
    if (title) {
      savedTitle = title;
    }

    // Enable eligible menu options. We have to move the dom options elements
    // instead of simply hiding to support webkit.
    for(var i in values) {
      //var menu = Drupal.settings.og_menu[values[i]];
      $('option', holder).each(function() {
        parts = $(this).val().split(':');
        if (Drupal.settings.og_menu[parts[0]] == values[i]) {
          $(this).appendTo('.menu-title-select');
          none = false;
        }
      });
    }
    // No option is eligible, disable the menu select
    if (none) {
      disabledOption.appendTo('.menu-title-select');
      inputTitle.val('');
      inputTitle.attr("disabled", "disabled");
      inputTitle.trigger('change');
      inputDelete.attr('checked', 'checked');
      $('.menu-title-select').attr("disabled", "disabled");
      $('.menu-title-select').val('');
    }
    else {
      // If an option exists with the initial value, set it. We do this because
      // we want to keep the original parent if user just adds a group to the node.
      if ($('.menu-title-select option[value='+originalParent+']')) {
        $('.menu-title-select').val(originalParent);
      }
    }
  };

  // Toggle function for OG select
  var toggleSelect = function() {
    toggle($(this).val());
  };

  // Toggle function for OG checkboxes
  var toggleCheckboxes = function() {
    var values = [];
    $('.og-audience:checkbox:checked').each(function() {
      values.push($(this).val());
    });
    toggle(values);
  };

  // Alter menu on OG select change and init
  if ($('select.og-audience').size()) {
    $('select.og-audience').change(toggleSelect).ready(toggleSelect);
  }

  // Alter menu on OG checkboxes change and init
  if ($('.og-audience:checkbox').size()) {
    $('.og-audience:checkbox').change(toggleCheckboxes).ready(toggleCheckboxes);
  }
}