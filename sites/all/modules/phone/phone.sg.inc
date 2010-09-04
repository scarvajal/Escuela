<?php
// $Id: phone.sg.inc,v 1.6 2010/07/19 22:34:08 thierrygd Exp $

/**
 * @file
 * CCK Field for Singapore phone numbers.
 */

function phone_sg_metadata() {
  // These strings are translated using t() on output.
  return array(
    'label' => 'Singapore Phone Numbers',
    'error' => '"%value" is not a valid Singapore phone number<br>Singapore phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_sg_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^[6]\d{7}$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Singapore Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_sg_phone_number($phonenumber, $field) {

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
