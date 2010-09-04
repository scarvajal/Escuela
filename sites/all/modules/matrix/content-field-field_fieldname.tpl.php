<?php
// $Id: content-field-field_fieldname.tpl.php,v 1.1.2.4 2009/05/13 12:34:40 aaron1234nz Exp $

/**
 * @file content-field.tpl.php
 * Default theme implementation to display the value of a field.
 *
 * Available variables:
 * - $node: The node object.
 * - $field: The field array.
 * - $items: An array of values for each item in the field array.
 * - $teaser: Whether this is displayed as a teaser.
 * - $page: Whether this is displayed as a page.
 * - $field_name: The field name.
 * - $field_type: The field type.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $label: The item label.
 * - $label_display: Position of label display, inline, above, or hidden.
 * - $field_empty: Whether the field has any valid value.
 *
 * Each $item in $items contains:
 * - 'view' - the themed view for that item
 *
 * @see template_preprocess_field()
 */
?>
<?php if (!$field_empty) : ?>
<div class="field field-type-<?php print $field_type_css ?> field-<?php print $field_name_css ?>">
  <?php if ($label_display == 'above') : ?>
    <div class="field-label"><?php print t($label) ?>:&nbsp;</div>
  <?php endif;?>
  <div class="field-items">
    <?php $count = 1;
    foreach ($items as $delta => $item) :
      if (!$item['empty']) : ?>
        <div class="field-item <?php print ($count % 2 ? 'odd' : 'even') ?>">
          <?php if ($label_display == 'inline') { ?>
            <div class="field-label-inline<?php print($delta ? '' : '-first')?>">
              <?php print t($label) ?>:&nbsp;</div>
          <?php } ?>
          <?php
            $prepared = matrix_format_prepare($field, $item);
            $links = matrix_format_prepare_links($node->nid, $field_name);
            
            //if you want to customize the formatting, manipulate $prepared before passing it to theme('matrix_table'...)
            foreach ($prepared as $row_index => $row) {
              foreach ($row as $column_index => $cell_value) {
                if ($row_index > 0 && $column_index > 0) {
                  $manipulated_data[$row_index][$column_index] = "<div style='color:red'>$cell_value</div>";
                }
                else {
                  $manipulated_data[$row_index][$column_index] = $cell_value;
                }
              }
            }
            
            print theme('matrix_table', $manipulated_data);
            print $links; //eg export link
          ?>
        </div>
      <?php $count++;
      endif;
    endforeach;?>
  </div>
</div>
<?php endif; ?>
