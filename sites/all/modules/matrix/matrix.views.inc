<?php
// $Id: matrix.views.inc,v 1.1.2.5 2009/12/31 17:38:15 develCuy Exp $

/**
* @file
* Views hooks implemented for the Matrix module.
*/

/**
 * Implementation of hook_views_data()
 */
function matrix_views_data() {
  foreach (content_fields() as $field) {
    if ($field['type'] == 'matrix') {
      $data['node_data_'. $field['field_name']] = array(
        'table' => array(
          'group' => 'Matrix',
          'join' => array(
            'node' => array(
              'table' => 'content_type_'. $field['type_name'],
              'left_field' => 'vid',
              'field' => 'vid',
            ),
          ),
        ),
        $field['field_name'] .'_value' => array(
          'field' => array(
            'title' => $field['widget']['label'] .' ('. $field['field_name'] .')',
            'help' => t('Appears on %type_name (table layout)', array('%type_name' => $field['type_name'])),
            'handler' => 'matrix_handler_field',
            'content_field_name' => $field['field_name'],
          ),
        ),
      );
      
      switch ($field['widget']['type']) {
        case 'table':
          $rows_elements = array_fill(0, count($field['widget']['default_value']), '0');
          break;
        case 'matrix':
          $rows_elements = unserialize($field['rows_elements']); 
          break;
      }
      $cols_elements = unserialize(str_replace("\r", "", $field['cols_elements']));
      if (!is_array($cols_elements))
        $cols_elements = array();

      foreach ($rows_elements as $row_index => $row) {
        foreach ($cols_elements as $col_index => $col) {
          $cell_ref = $row_index .'_'. $col_index;
          $cell_name = $col['#title'] .' x '. $row['#title'];
          
          $data['node_data_'. $field['field_name'] .'_'. $cell_ref] = array(
            'table' => array(
              'group' => 'Matrix',
              'join' => array(
                'node' => array(
                  'table' => 'content_type_'. $field['type_name'],
                  'left_field' => 'vid',
                  'field' => 'vid',
                ),
              ),
            ),
            $field['field_name'] .'_'. $cell_ref .'_value' => array(
              'field' => array(
                'title' => $field['widget']['label']  .' cell '. $cell_name .' ('. $field['field_name'] .')',
                'help' => t('Appears on %type_name', array('%type_name' => $field['type_name'])),
                'handler' => 'matrix_handler_cell',
                'content_field_name' => $field['field_name'],
                'row_index' => $row_index,
                'col_index' => $col_index,
              ),
              'filter' => array(
                'title' => $field['widget']['label']  .' cell '. $cell_name .' ('. $field['field_name'] .')',
                'help' => t('Appears on %type_name', array('%type_name' => $field['type_name'])),
                'handler' => 'matrix_handler_filter_cell',
              ),
             /* 'argument' => array(
                'handler' => 'matrix_handler_argument_cell',
                'parent' => 'views_handler_argument_numeric', // make sure parent is included
                'name field' => 'title', // the field to display in the summary.
              ),
              'sort' => array(
                'handler' => 'matrix_handler_sort_cell',
              ),*/
            ),
          ); 
        }
      }
    }
  }
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function matrix_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'matrix'),
    ),
    'handlers' => array(
      'matrix_handler_field' => array(
        'parent' => 'views_handler_field',
        'file' => 'matrix_handler_field.inc',
      ),
      'matrix_handler_cell' => array(
        'parent' => 'views_handler_field',
        'file' => 'matrix_handler_cell.inc',
      ),
      'matrix_handler_filter_cell' => array(
        'parent' => 'views_handler_filter_string',
        'file' => 'views_handler_filter_cell.inc',
      ),
     /* 'matrix_handler_sort_cell' => array(
        'parent' => 'views_handler_sort',
        'file' => 'matrix_handler_sort_cell.inc',
      ),
      'matrix_handler_arguments_cell' => array(
        'parent' => 'views_handler_argument',
        'file' => 'matrix_handler_arguments_cell.inc',
      ),*/
    ),
  );
}