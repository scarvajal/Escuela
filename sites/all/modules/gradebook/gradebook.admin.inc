<?php
// $Id: gradebook.admin.inc,v 1.1.2.2 2008/12/30 22:02:09 mgn Exp $

/**
 * @file
 * Admininistration pages for gradebook.module
 */

/**
 * Returns an overview list of existing gradebooks
 */
function gradebook_admin_list_page() {
  $vid = gradebookapi_get_vid();

  $header = array(
    array('data' => t('Name'), 'field' => 't.name', 'sort' => 'asc'),
    array('data' => t('Operations')),
  );

  $sql  = 'SELECT DISTINCT t.tid, t.name FROM {term_data} t INNER JOIN {term_hierarchy} h ON t.tid = h.tid WHERE h.parent = 0 AND t.vid = '. $vid;
  $sql .= tablesort_sql($header, 'weight, ');
  $result = pager_query($sql, variable_get('gradebooks_per_page', 25));

  while ($term = db_fetch_object($result)) {
    $rows[] = array('name' => l($term->name, 'gradebook/'. $term->tid), 'operations' => l(t('edit'), 'admin/gradebook/gradebook/edit/'. $term->tid));
  }

  $output = theme('table', $header, $rows);
  $output .= theme('pager');

  return $output;
}

function gradebook_add_page() {
  return drupal_get_form('gradebook_gradebook_form');
}

function gradebook_edit_page($tid=-1) {
  // TODO: check to make sure gradebook tid is valid

  if (isset($_POST['op']) && $_POST['op']== t('Delete') || isset($_POST['confirm'])) {
    return drupal_get_form('gradebook_confirm_gradebook_delete', $tid);
  }

  $term = taxonomy_get_term($tid);
  return drupal_get_form('gradebook_gradebook_form', (array)$term);
}


function gradebook_gradebook_form($form_state, $edit = array()) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Gradebook name'),
    '#default_value' => isset($edit['name']) ? $edit['name'] : '',
    '#maxlength' =>  64,
    '#description' => t('The gradebook name is used to identify related assignments/grades.'),
    '#required' => TRUE,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($edit['description']) ? $edit['description'] : '',
    '#description' => t('The gradebook description can give users more information about the assignments/grades it contains.'),
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => isset($edit['weight']) ? $edit['weight'] : 0,
    '#description' => t('When listing gradebooks, those with lighter (smaller) weights get listed before gradebooks with heavier (larger) weights. Gradebooks with equal weights are sorted alphabetically.'),
  );

  $form['vid'] = array('#type' => 'hidden', '#value' => gradebookapi_get_vid());
  $form['submit' ] = array('#type' => 'submit', '#value' => t('Save'));
  if (isset($edit['tid'])) {
    $form['delete'] = array('#type' => 'submit', '#value' => t('Delete'));
    $form['tid'] = array('#type' => 'hidden', '#value' => $edit['tid']);
  }

  return $form;
}

function gradebook_gradebook_form_submit($form, &$form_state) {
  $status = taxonomy_save_term($form_state['values']);
  switch ($status) {
    case SAVED_NEW:
      drupal_set_message(t('Created new gradebook %term.', array('%term' => $form_state['values']['name'])));
      break;
    case SAVED_UPDATED:
      drupal_set_message(t('The gradebook %term has been updated.', array('%term' => $form_state['values']['name'])));
      break;
  }
  $form_state['redirect'] = 'admin/gradebook/gradebook';
}

/**
 * Returns a confirmation page for deleting a gradebook taxonomy term.
 *
 * @param $tid ID of the term to be deleted
 */
function gradebook_confirm_gradebook_delete($form_state, $tid) {
  // TODO: make sure this is a valid gradebook term

  $term = taxonomy_get_term($tid);

  $form['tid'] = array('#type' => 'value', '#value' => $tid);
  $form['name'] = array('#type' => 'value', '#value' => $term->name);

  return confirm_form($form,
                      t('Are you sure you want to delete the gradebook %name?', array('%name' => $term->name)),
                      'admin/gradebook/gradebook',
                      t('Deleting a gradebook will delete all associated grades as well. This action cannot be undone.'),
                      t('Delete'),
                      t('Cancel'));
}

/**
 * Implementation of forms api _submit call. Deletes a gradebook after confirmation.
 */
function gradebook_confirm_gradebook_delete_submit($form, &$form_state) {
  // TODO: delete grades
  taxonomy_del_term($form_state['values']['tid']);
  drupal_set_message(t('The gradebook %term and all associated grades have been deleted.', array('%term' => $form_state['values']['name'])));
  watchdog('gradebook', 'gradebook: deleted %term and associated grades.', array('%term' => $form_state['values']['name']));

  $form_state['redirect'] = 'admin/gradebook/gradebook';
}

function gradebook_admin_settings() {
  $form = array();

  drupal_set_title(t('Gradebook configuration'));

  $form['sitewide'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Sitewide gradebook settings'),
    '#weight'      => -1,
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#description' => t('Any student and teacher roles selected here will apply to ALL gradebooks. If you are using the OG_Gradebook module, do not select any names here and gradebooks will be formed by group membership. Otherwise, any roles selected here will appear in the gradebook for each group.'),
  );

  $roles = user_roles();
  unset($roles[DRUPAL_ANONYMOUS_RID]);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);

  $sel_roles = (array) variable_get('gradebook_student_rids', array());
  $default = array();
  foreach ($sel_roles as $rid => $value) {
    if ($value) {
      $default[] = $rid;
    }
  }
  $form['sitewide']['gradebook_student_rids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Student roles'),
    '#default_value' => $default,
    '#options' => $roles,
    '#required' => FALSE,  // permit no sitewide student roles when using organic groups...
  );

  $sel_roles = (array) variable_get('gradebook_teacher_rids', array());
  $default = array();
  foreach ($sel_roles as $rid => $value) {
    if ($value) {
      $default[] = $rid;
    }
  }
  $form['sitewide']['gradebook_teacher_rids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Teacher roles'),
    '#default_value' => $default,
    '#options' => $roles,
    '#required' => FALSE,  // permit no sitewide teacher roles when using organic groups...
  );

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General gradebook settings'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['general']['gradebook_empty_grade'] = array(
    '#type' => 'textfield',
    '#title' => t('Empty grade'),
    '#default_value' => variable_get('gradebook_empty_grade', '--'),
    '#description' =>  t('This the text displayed when no grade has been entered.'),
    '#required' => TRUE,
  );

  $number = drupal_map_assoc(array(10, 25, 50, 75, 100));
  $form['general']['gradebooks_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Gradebooks per page'),
    '#default_value' => variable_get('gradebooks_per_page', 25),
    '#options' => $number,
    '#description' => t('The default number of gradebooks displayed per page.'),
  );

  return system_settings_form($form);
}
