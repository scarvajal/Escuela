<?php
// $Id: phone.be.inc,v 1.6 2010/07/19 22:34:08 thierrygd Exp $

/**
 * @file
 * CCK Field for Belgian phone numbers.
 */

function phone_be_metadata() {
  // These strings are translated using t() on output.
  return array(
    'label' => 'Belgian Phone Numbers',
    'error' => '"%value" is not a valid Belgian phone number<br>Belgian phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_be_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^0[1-9]\d{7,8}$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Belgian Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_be_phone_number($phonenumber, $field) {

  //$phonenumber = trim($phonenumber);

   // do some formatting on the phone number

/* ==> to be done ==> add the country code 
   if ($field['phone_country_code']) {
      if ($matches[1] != "+39") {
  	$phonenumber = "+39" . " " . $phonenumber;
      }
   }
*/ 
   return $phonenumber;
}
