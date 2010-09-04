<?php
// $Id: phone.ua.inc,v 1.6 2010/07/19 22:34:08 thierrygd Exp $

/**
 * @file
 * CCK Field for Ukrainian phone numbers.
 */

function phone_ua_metadata() {
  // These strings are translated using t() on output.
  return array(
    'label' => 'Ukraine Phone Numbers',
    'error' => '"%value" is not a valid Ukrainina mobile phone number<br>Ukraine phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_ua_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^((8|\+38)-?)?(\(?044\)?)?-?\d{3}-?\d{2}-?\d{2}$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Unkraine Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_ua_phone_number($phonenumber, $field) {

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
