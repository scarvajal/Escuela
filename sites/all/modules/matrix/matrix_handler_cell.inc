<?php
// $Id: matrix_handler_cell.inc,v 1.1.2.2 2009/12/31 17:38:15 develCuy Exp $

/**
 * Cell handler to present a cell from the Matrix field to the user.
 */
class matrix_handler_cell extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['vid'] = 'vid';
    $this->content_field = content_fields($this->definition['content_field_name']);
    $this->row_index = $this->definition['row_index'];
    $this->col_index = $this->definition['col_index'];
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['label'] = array('default' => 'Matrix', 'translatable' => TRUE);
    return $options;
  }
  
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  
  function render($values) {
    $node->vid = $values->{$this->aliases['vid']};
    $field_info = matrix_field('load', $node, $this->content_field, $node, NULL, NULL);
    $prepared = matrix_format_prepare($field_info[$this->content_field['field_name']]);
 
    return $prepared[$this->row_index + 1][$this->col_index + 1];
  }
}
