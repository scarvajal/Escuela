// $Id: cck_phone.js,v 1.1 2010/07/08 11:20:27 ckng Exp $

Drupal.PhoneNumber = Drupal.PhoneNumber || {};

/**
 * Filters checkboxes based on their label.
 * This code is shamelessly taken from checkbox_filter
 */
Drupal.PhoneNumber.filter = function() {
  var field = $(this);
  var checkboxes = $('.form-checkboxes .form-item', field.parent().parent());
  var found = false;
  var label = "";
  var option = null;
  for (var i = 0; i < checkboxes.length; i++) {
    option = checkboxes.eq(i);
    label = Drupal.PhoneNumber.trim(option.text());
    if (label.toUpperCase().indexOf(field.val().toUpperCase()) < 0) {
      option.hide();
    } else {
      option.show();
    }
  }
}

/**
 * Trims whitespace from strings
 */
Drupal.PhoneNumber.trim = function(str) {
	var	str = str.replace(/^\s\s*/, ''),
		ws = /\s/,
		i = str.length;
	while (ws.test(str.charAt(--i)));
	return str.slice(0, i + 1);
}

/**
 * Check/Uncheck all checkboxes
 */
Drupal.PhoneNumber.checkall = function(e) {
  var field = $(this);
  var checkboxes = $('.form-checkboxes .form-item:visible .form-checkbox', field.parent().parent());

  var checked = (field.text() == Drupal.t('Select all'));
  if (checked) {
    checkboxes.attr('checked', true);
    field.text(Drupal.t('Deselect all'));
  }
  else {
    checkboxes.attr('checked', false);
    field.text(Drupal.t('Select all'));
  }
}

/**
 * Attach a filtering textfield to checkboxes.
 */
Drupal.behaviors.PhoneNumber = function (context) {
  var form = '<div class="form-item">'
           + '  <label>' + Drupal.t('Filter') + ':</label> '
           + '  <input class="cck-phone-filter" type="text" size="16" />'
           + '</div>'
           + '<div class="form-item">'
           + '  <a class="cck-phone-check" href="javascript://">' + Drupal.t('Select all') + '</a>'
           + '</div>';
  $('.cck-phone-settings .form-checkboxes', context).before(form);
  $('input.cck-phone-filter').bind('keyup', Drupal.PhoneNumber.filter);
  $('a.cck-phone-check').bind('click', Drupal.PhoneNumber.checkall);
}