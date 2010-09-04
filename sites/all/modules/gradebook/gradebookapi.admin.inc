<?php
// $Id: gradebookapi.admin.inc,v 1.1.2.1 2008/12/20 04:13:12 mgn Exp $

/**
 * @file
 * gradebookapi.admin.inc: Administration pages for gradebookapi
 */

function gradebookapi_admin_settings() {
  $form = array();
  $form['#submit'][]= 'gradebookapi_admin_settings_submit'; // custom submit handler

  drupal_set_title(t('Gradebook API configuration'));

  $vid = gradebookapi_get_vid();
  $vocabulary = taxonomy_vocabulary_load($vid);

  $form['nodes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Assignment Types'),
    '#multiple' => TRUE,
    '#default_value' => empty($vocabulary->nodes) ? array(): $vocabulary->nodes,
    '#options' => array_map('check_plain', node_get_types('names')),
    '#description' => t('A list of node types you want to treat as assignments.'),
  );

  return system_settings_form($form);
}

function gradebookapi_admin_settings_submit($form, &$form_state) {

  $vid = gradebookapi_get_vid();
  $vocabulary = taxonomy_vocabulary_load($vid);
  $n =array_filter($form_state['values']['nodes']);
  $vocabulary->nodes = empty($n) ? array() : $n;
  $vocab_array = (array)$vocabulary;
  switch (taxonomy_save_vocabulary($vocab_array) ) {  // must pass array in! not vocab object!
    case SAVED_NEW:
      drupal_set_message(t('Created new vocabulary %name.', array('%name' => $vocabulary->name)));
      watchdog('gradebook', 'Created new vocabulary %name.', array('%name' => $vocabulary->name), WATCHDOG_NOTICE, l(t('edit'), 'admin/content/taxonomy/edit/vocabulary/'. $vid));
      break;
    case SAVED_UPDATED:
      drupal_set_message(t('Updated vocabulary %name.', array('%name' => $vocabulary->name)));
      watchdog('gradebook', 'Updated vocabulary %name.', array('%name' => $vocabulary->name), WATCHDOG_NOTICE, l(t('edit'), 'admin/content/taxonomy/edit/vocabulary/'. $vid));
      break;
  }
  $form_state['redirect'] = 'admin/gradebook';

// TODO: look over this code
  // rebuild grades in each gradebook
  //$terms = taxonomy_get_tree($vid, 0, -1, 1);
  //foreach ($terms as $term) {
  //  gradebookapi_rebuild_grades($term->tid);
  //}

  //drupal_set_message(t('Updated gradebookapi settings.'));
}
