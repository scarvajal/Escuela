*************
** README: **
*************

DESCRIPTION:
-----------
This module provides a field type for cck with table view of form elements.
It is also possible to create use the element exposed by this module in the FAPI


REQUIREMENTS:
-------------
The matrix.module requires the content.module to be installed.


INSTALLATION:
-------------

1. Place the entire matrix directory into your Drupal modules/
   directory.


2. Enable the matrix module by navigating to:

     administer > site configuration > modules

   Enabling the matrix module will create the necessary database tables for you.


USING THE MATRIX MODULE (CCK):
------------------------------
After enableing the module, you can create a new field. Choose the Matrix field. On the configuration page,
there is an interface for adding rows and columns.  A live preview of your field will also be generated.

USING THE MATRIX MODULE (Form element):
------------------------------

/**
 * Implementation of hook_menu()
 */
function matrix_menu() {
  $items['matrix/example'] = array(
    'title' => 'Example use of matrix as a form element',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('matrix_example'),
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );
  return $items;
}

/**
 * Form Definition
 */
function matrix_example() {
  $form['matrixfield'] = array(
    '#type' => 'matrix',
    '#mode' => 'cols',
    '#title' => 'Example matrix element',
    '#description' => 'This is how you use it!',
    '#cols_elements' => array(
      array(
        '#type' => 'textfield',
        '#title' => 'Textbox 1',
        '#default_value' => 'One',
        '#required' => TRUE,
      ),
      array(
        '#type' => 'title',
        '#title' => 'Title 1',
      ),
      array(
        '#type' => 'select',
        '#title' => 'Select 1',
        '#options' => array('one' => 'One', 'two' => 'Two', 'three' => 'Three'),
        '#default_value' => 'two',
      ),
      array(
        '#type' => 'checkbox',
        '#title' => 'Checkbox 1',
        '#default_value' => TRUE,
      ),
      array(
        '#type' => 'radios',
        '#title' => 'Radios 1',
        '#options' => array('one' => 'One', 'two' => 'Two', 'three' => 'Three'),
        '#default_value' => 'two',
      ),
    ),
    '#rows_elements' => array(
      array(
        '#title' => 'Row 1'
      ),
      array(
        '#title' => 'Row 2'
      ),
      array(
        '#title' => 'Row 3'
      ),      
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}

/**
 * Implementation of hook_submit()
 */
function matrix_example_submit($form_id, $form_state) {
  print_r($form_state['values']['matrixfield']);
  die();
}


THEMEING:
---------
It is possible to alter the display of a CCK matrix field using the theme layer.
To do this you first need to copy two files to your theme directory:
* sites/all/modules/cck/theme/content-field.tpl.php file to your theme directory
* sites/all/modules/matrix/content-field-field_fieldname.tpl.php
Rename the second .tpl.php file, replacing "fieldname" with the name of your field
Rebuild your sites theme registry (admin >> performance >> clear cache)
Modify this file to do the theme changes you desire.

TODO:
-----
 * Allow users/administrators to add cols and rows dynamically
 * Add the facility to use any cck field in the matrix
 

Author:
-------
Original Author:
Matthias Hutterer
mh86@drupal.org
m_hutterer@hotmail.com

Current Maintainer:
Aaron Fulton
aaron@webtolife.org