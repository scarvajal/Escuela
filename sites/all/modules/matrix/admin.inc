<?php
// $Id: admin.inc,v 1.1.2.8 2009/12/31 17:38:15 develCuy Exp $

/**
 * @file
 * Provides functions used in the creation of matrix fields.
 */
function matrix_settings_reorder_save() {
  $field_name = $_REQUEST['field_name'];
  $source = (int)$_REQUEST['source'];
  $destination = (int)$_REQUEST['destination'];
  $rc = $_REQUEST['rc'];
  $mode = $_REQUEST['mode'];
  $cache_response = cache_get('matrix-'. $rc .'-'. $field_name); //load existing elements from cache

  $elements = (array)$cache_response->data;

  $move_element = $elements[$source];

  foreach ($elements as $id => $element) {
    if ($source < $destination) {
      if ($id != $source) {
        $fixed_elements[] = $element;
      }
      if ($id == $destination) {
        $fixed_elements[] = $move_element;
      }
    }
    else {
      if ($id == $destination) {
        $fixed_elements[] = $move_element;
      }
      if ($id != $source) {
        $fixed_elements[] = $element;
      }
    }
  }

  $elements = array_values($fixed_elements); //this rekeys the array so it remains sequential.

  cache_set('matrix-'. $rc .'-'. $field_name, $elements); //save all elements back to the cache

  $list .= theme('matrix_settings_list', $elements, $rc);

  $rows_elements = cache_get('matrix-rows-'. $field_name); //load existing elements from cache
  $cols_elements = cache_get('matrix-cols-'. $field_name); //load existing elements from cache
  $preview = drupal_get_form('matrix_settings_preview', $field_name, $mode, $rows_elements->data, $cols_elements->data);

  echo drupal_to_js(array('list' => $list, 'data' => serialize($elements), 'preview' => $preview));
  exit();
}

/**
 * AJAX callback for saving an individual element
 * Takes parameters from $_REQUEST
 * Saves the data into the Drupal cache
 * Echos JSON data which contains:
 *  serialized data (which is what will be eventually saved into the database)
 *  list of elements for row/column
 */
function matrix_settings_throbber_save() {
  $field_name = $_REQUEST['field_name'];
  $element_id = $_REQUEST['element_id'];
  $rc = $_REQUEST['rc'];
  $mode = $_REQUEST['mode'];

  $cache_response = cache_get('matrix-'. $rc .'-'. $field_name); //load existing elements from cache

  $elements = (array)$cache_response->data;

  //build the new element
  $data['#type'] = $_REQUEST['element_type'];
  $data['#title'] = $_REQUEST['title'];
  $data['#options'] = $_REQUEST['options'];
  $data['#validation'] = $_REQUEST['validation'];
  $data['#size'] = $_REQUEST['size'] != 'undefined' ? $_REQUEST['size'] : '';
  $data['#required'] = ($_REQUEST['required'] == 'true') ? 1 : 0;
  $data['#calc_method'] = $_REQUEST['calc_method'];
  $data['#php'] = ($_REQUEST['php'] == 'true') ? 1 : 0;

  if ($element_id !== '') {
    $elements[$element_id] = $data;
  }
  else {
    $elements[] = $data;
  }
  $elements = array_values($elements); //this rekeys the array so it remains sequential.

  cache_set('matrix-'. $rc .'-'. $field_name, $elements); //save all elements back to the cache

  $list .= theme('matrix_settings_list', $elements, $rc);

  $rows_elements = cache_get('matrix-rows-'. $field_name); //load existing elements from cache
  $cols_elements = cache_get('matrix-cols-'. $field_name); //load existing elements from cache
  $preview = drupal_get_form('matrix_settings_preview', $field_name, $mode, $rows_elements->data, $cols_elements->data);

  echo drupal_to_js(array('list' => $list, 'data' => serialize($elements), 'preview' => $preview));
  exit();
}

/**
 * Menu callback to delete an element
 * This is part one of the delete process.
 * Accepts parameters via $_REQUEST
 * Echos a delete confirm form.
 */
function matrix_settings_throbber_delete() {
  $field_name = $_REQUEST['field_name'];
  $element_id = $_REQUEST['element_id'];
  $confirm = $_REQUEST['confirm'];
  $rc = $_REQUEST['rc'];
  $cache_response = cache_get('matrix-'. $rc .'-'. $field_name); //load existing elements from cache
  $elements = (array)$cache_response->data;

  if ($confirm == 'confirmed') {
    unset($elements[$element_id]);
    cache_set('matrix-'. $rc .'-'. $field_name, $elements); //save all elements back to the cache
    
    $list .= theme('matrix_settings_list', $elements, $rc);
    
    echo drupal_to_js(array('list' => $list, 'data' => serialize($elements)));
    exit();
  }
  else {
    $output = drupal_get_form('matrix_delete_button');
    echo $output;
    exit();
  }
}

/**
 * Form definition function
 * @return array form definition.
 */
function matrix_delete_button() {
  $rc = $_REQUEST['rc'];
  $form['delete'] = array(
    '#type' => 'fieldset',
    '#title' => t('Delete'),
  );
  $form['delete']['text'] = array(
    '#type' => 'markup',
    '#value' => t('Are you sure you want to delete this element?') .'<br />',
  );
  $form['delete']['delete_confirm'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
    '#attributes' => array('class' => "matrix-$rc"),
  );
  $form['delete']['delete_cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => "matrix-$rc"),
  );
  $form['delete']['element_id'] = array(
    '#type' => 'hidden',
    '#value' => $_REQUEST['element_id'],
  );
  return $form;
}

/**
 * Menu callback for createing a new row/column
 * $_REQUEST contains the settings of an exising row/column
 * @return HTML form.
 */
function matrix_settings_throbber_callback() {
  echo drupal_get_form('matrix_settings_throbber_callback_form');
  exit();
}

/**
 * Form definition for the throbber
 * This list is called when a new field is added via the settings page or a field is edited
 *
 * @return form definition
 */
function matrix_settings_throbber_callback_form($form_state) {
  $field_name = $form_state['post']['field_name'];
  $field_type = $form_state['post']['field_type'];
  $rc = $form_state['post']['rc'];
  $mode =  $form_state['post']['mode'];

  if ($form_state['post']['element_id'] != 'undefined') {
    $element_id = $form_state['post']['element_id'];
    $cache_response = cache_get('matrix-'. $rc .'-'. $field_name); //load existing elements from cache  
    $elements = (array)$cache_response->data;
    $default_values = $elements[$element_id];
  }
  if (!empty($form_state['post']['element_type']) && $form_state['post']['element_type'] != 'undefined') {
    $element_type = $form_state['post']['element_type'];
  }
  else {
     $element_type = $default_values['#type'];
  }

  $form['element'] = array(
    '#type' => 'fieldset',
    '#title' => t('add/edit'),
  );
  $form['element']['element_id'] = array(
    '#type' => 'hidden',
    '#value' => $element_id,
    '#attributes' => array('class' => "matrix-$rc"),
  );
  if ($mode == $rc || $field_type == 'table') {
    $options = array('' => t('- select -'), 'title' => t('Title only'), 'textfield' => t('Textfield'), 'select' => t('Select'), 'checkbox' => t('Checkbox'), 'radios' => t('Radio buttons'), 'calculation' => t('Calculation'));
  }
  else {
    $options = array('' => t('- select -'), 'title' => t('Title only'));
  }
  $form['element']['element_type'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Widget type'),
    '#attributes' => array('class' => "matrix-$rc"),
    '#default_value' => $element_type,
  );

  if (!empty($element_type)) { //a widget type has been chosen - render some more form
    $form['element']['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#size' => 10,
      '#default_value' => $default_values['#title'],
      '#attributes' => array('class' => "matrix-$rc"),
    );

    switch ($element_type) {
      case 'textfield':
        $form['element']['size'] = array(
          '#type' => 'textfield',
          '#title' => t('Size'),
          '#size' => 5,
          '#default_value' => !empty($default_values['#size']) ? $default_values['#size'] : 5,
          '#attributes' => array('class' => "matrix-$rc"),
        );
        $form['element']['validation'] = array(
          '#type' => 'select',
          '#title' => t('Validation'),
          '#options' => array('none' => t('None'), 'numeric' => t('Numeric'), 'custom' => t('Custom')),
          '#default_value' => !empty($default_values['#validation']) ? $default_values['#validation'] : 5,
          '#attributes' => array('class' => "matrix-$rc"),
        );
        break;
      case 'select':
      case 'radios':        
        $form['element']['options'] = array(
          '#type' => 'textarea',
          '#title' => t('Options'),
          '#description' => t('One option per line.'),
          '#cols' => 20,
          '#rows' => 6,
          '#default_value' => $default_values['#options'],
          '#attributes' => array('class' => "matrix-$rc"),
        );
        if (user_access('use php for matrix options')) {
          $form['element']['php'] = array(
            '#type' => 'checkbox',
            '#title' => t('Evaluate as php'),
            '#description' => t('Tick to evaluate the contents of the options box as php.  Note do not include <?php ?> tags.'),
            '#default_value' => $default_values['#php'],
            '#attributes' => array('class' => "matrix-$rc"),
          );
        }
        break;
      
      case 'calculation':
        $form['element']['calc_method'] = array(
          '#type' => 'select',
          '#title' => t('Calculation type'),
          '#options' => array('select' => t('- select one -'), 'sum' => t('Sum'), 'average' => t('Average'), 'max' => t('Maximum'), 'min' => t('Minimum'), 'max' => t('Maximum'), 'mode' => t('Most common')),
          '#description' => t('The calculation type.  Note that apart from "Most common" the other calculation types require numeric data.'),
          '#default_value' => $default_values['#calc_method'],
          '#attributes' => array('class' => "matrix-$rc"),
        );
        break;

      case 'checkbox':
      case 'title':
        break;
    }

    $form['element']['required'] = array(
      '#type' => 'checkbox',
      '#title' => t('Required'),
      '#default_value' => $default_values['#required'],
      '#attributes' => array('class' => "matrix-$rc"),
    );
    $form['element']['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#attributes' => array('class' => "matrix-$rc"),
    );
    $form['element']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#attributes' => array('class' => "matrix-$rc"),
    );
    $form['element']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#attributes' => array('class' => "matrix-$rc"),
    );
  }
  return $form;
}
