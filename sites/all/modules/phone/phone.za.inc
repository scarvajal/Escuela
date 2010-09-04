<?php
// $Id: phone.za.inc,v 1.3 2010/07/19 22:34:08 thierrygd Exp $

/**
 * @file
 * CCK Field for South African phone numbers.
 */

function phone_za_metadata() {
  // These strings are translated using t() on output.
  return array(
    'label' => 'South African Phone Numbers',
    'error' => '"%value" is not a valid South African phone number!<br>Czech phone numbers should ...',
  );
}

/**
 * Verifies that $phonenumber is a valid South African phone number
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_za_phone_number($phonenumber) {

  $phonenumber = trim($phonenumber);

  // define regular expression
  $regex = '/^((?:\+27|27)|0)[ ]*((\d{2})(-| )?(\d{3})(-| )?(\d{4})|(\d{2})( |-)(\d{7}))$/';
  
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Convert a valid South African phone number into standard ... format
 *
 * @param $phonenumber must be a valid  ... digit number (with optional international prefix)
 *
 */
function format_za_phone_number($phonenumber, $field) {

  // define regular expression
  $regex = '/^((?:\+27|27)|0)[ ]*((\d{2})(-| )?(\d{3})(-| )?(\d{4})|(\d{2})( |-)(\d{7}))$/';

  // get digits of phone number
  preg_match($regex, $phonenumber, $matches);

  if ($field['phone_country_code']) {
    	$phonenumber = '+27' . ' ' . $matches[2] .'-'. $matches[3] .'-'. $matches[4];
  }
  else {
  	$phonenumber = $matches[2] .'-'. $matches[3] .'-'. $matches[4];
  }

  return $phonenumber;
}
