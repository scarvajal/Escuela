<?php
// $Id: cck_phone_countrycodes.inc,v 1.1 2010/07/08 11:20:27 ckng Exp $

/**
 * @file
 * Defines country codes for Phone Number.
 * Provide country name and international codes per country codes.
 */

/**
 * Get all the country codes for supported countries.
 *
 * @param $cc
 *   Optional, two character country code. If this is ommitted all country codes
 *   will be returned.
 * @return
 *   If no country code is provided an array keyed by country code, values are
 *   arrays with a 'country' and 'code' values. If an invalid $cc is provided,
 *   FALSE will be returned. If the country code is valid the country code for
 *   that country will be returned.
 */
function cck_phone_countrycodes($cc = NULL) {
  // Alpha-2 codes from ISO 3166-1 http://en.wikipedia.org/wiki/ISO_3166-1
  // Country codes from http://en.wikipedia.org/wiki/Country_calling_code
  static $country_code = array(
    'af' => array('country' => 'Afghanistan', 'code' => '+93'),
    'al' => array('country' => 'Albania', 'code' => '+355'),
    'dz' => array('country' => 'Algeria', 'code' => '+213'),
    'as' => array('country' => 'American Samoa', 'code' => '+1'),
    'ad' => array('country' => 'Andorra', 'code' => '+376'),
    'ao' => array('country' => 'Angola', 'code' => '+244'),
    'ai' => array('country' => 'Anguilla', 'code' => '+1'),
    'ag' => array('country' => 'Antigua and Barbuda', 'code' => '+1'),
    'ar' => array('country' => 'Argentina', 'code' => '+54'),
    'am' => array('country' => 'Armenia', 'code' => '+374'),
    'aw' => array('country' => 'Aruba', 'code' => '+297'),
    'au' => array('country' => 'Australia', 'code' => '+61'),
    'at' => array('country' => 'Austria', 'code' => '+43'),
    'az' => array('country' => 'Azerbaijan', 'code' => '+994'),
    'bs' => array('country' => 'Bahamas, The', 'code' => '+1'),
    'bh' => array('country' => 'Bahrain', 'code' => '+973'),
    'bd' => array('country' => 'Bangladesh', 'code' => '+880'),
    'bb' => array('country' => 'Barbados', 'code' => '+1'),
    'by' => array('country' => 'Belarus', 'code' => '+375'),
    'be' => array('country' => 'Belgium', 'code' => '+32'),
    'bz' => array('country' => 'Belize', 'code' => '+501'),
    'bj' => array('country' => 'Benin', 'code' => '+229'),
    'bm' => array('country' => 'Bermuda', 'code' => '+1'),
    'bt' => array('country' => 'Bhutan', 'code' => '+975'),
    'bo' => array('country' => 'Bolivia', 'code' => '+591'),
    'ba' => array('country' => 'Bosnia and Herzegovina', 'code' => '+387'),
    'bw' => array('country' => 'Botswana', 'code' => '+267'),
    'br' => array('country' => 'Brazil', 'code' => '+55'),
    'io' => array('country' => 'British Indian Ocean Territory', 'code' => '+246'),
    'vg' => array('country' => 'British Virgin Islands', 'code' => '+1'),
    'bn' => array('country' => 'Brunei', 'code' => '+673'),
    'bg' => array('country' => 'Bulgaria', 'code' => '+359'),
    'bf' => array('country' => 'Burkina Faso', 'code' => '+226'),
    'bi' => array('country' => 'Burundi', 'code' => '+257'),
    'kh' => array('country' => 'Cambodia', 'code' => '+855'),
    'cm' => array('country' => 'Cameroon', 'code' => '+237'),
    'ca' => array('country' => 'Canada', 'code' => '+1'),
    'cv' => array('country' => 'Cape Verde', 'code' => '+238'),
    'ky' => array('country' => 'Cayman Islands', 'code' => '+1'),
    'cf' => array('country' => 'Central African Republic', 'code' => '+236'),
    'td' => array('country' => 'Chad', 'code' => '+235'),
    'cl' => array('country' => 'Chile', 'code' => '+56'),
    'cn' => array('country' => 'China', 'code' => '+86'),
    'cx' => array('country' => 'Christmas Island', 'code' => '+61'),
    'cc' => array('country' => 'Cocos-Keeling Islands', 'code' => '+61'),
    'co' => array('country' => 'Colombia', 'code' => '+57'),
    'km' => array('country' => 'Comoros', 'code' => '+269'),
    'cg' => array('country' => 'Congo, Republic of the', 'code' => '+242'),
    'cd' => array('country' => 'Congo, Democratic Republic of', 'code' => '+243'),
    'ck' => array('country' => 'Cook Islands', 'code' => '+682'),
    'cr' => array('country' => 'Costa Rica', 'code' => '+506'),
    'hr' => array('country' => 'Croatia', 'code' => '+385'),
    'cu' => array('country' => 'Cuba', 'code' => '+53'),
    'cy' => array('country' => 'Cyprus', 'code' => '+357'),
    'cz' => array('country' => 'Czech Republic', 'code' => '+420'),
    'dk' => array('country' => 'Denmark', 'code' => '+45'),
    'dj' => array('country' => 'Djibouti', 'code' => '+253'),
    'dm' => array('country' => 'Dominica', 'code' => '+1'),
    'do' => array('country' => 'Dominican Republic', 'code' => '+1'),
    'tp' => array('country' => 'East Timor', 'code' => '+670'),
    'ec' => array('country' => 'Ecuador', 'code' => '+593'),
    'eg' => array('country' => 'Egypt', 'code' => '+20'),
    'sv' => array('country' => 'El Salvador', 'code' => '+503'),
    'gq' => array('country' => 'Equatorial Guinea', 'code' => '+240'),
    'er' => array('country' => 'Eritrea', 'code' => '+291'),
    'ee' => array('country' => 'Estonia', 'code' => '+372'),
    'et' => array('country' => 'Ethiopia', 'code' => '+251'),
    'fk' => array('country' => 'Falkland Islands', 'code' => '+500'),
    'fo' => array('country' => 'Faroe Islands', 'code' => '+298'),
    'fj' => array('country' => 'Fiji', 'code' => '+679'),
    'fi' => array('country' => 'Finland', 'code' => '+358'),
    'fr' => array('country' => 'France', 'code' => '+33'),
    'gf' => array('country' => 'French Guiana', 'code' => '+594'),
    'pf' => array('country' => 'French Polynesia', 'code' => '+689'),
    'ga' => array('country' => 'Gabon', 'code' => '+241'),
    'gm' => array('country' => 'Gambia, The', 'code' => '+220'),
    'ge' => array('country' => 'Georgia', 'code' => '+995'),
    'de' => array('country' => 'Germany', 'code' => '+49'),
    'gh' => array('country' => 'Ghana', 'code' => '+233'),
    'gi' => array('country' => 'Gibraltar', 'code' => '+350'),
    'gr' => array('country' => 'Greece', 'code' => '+30'),
    'gl' => array('country' => 'Greenland', 'code' => '+299'),
    'gd' => array('country' => 'Grenada', 'code' => '+1'),
    'gp' => array('country' => 'Guadeloupe', 'code' => '+590'),
    'gu' => array('country' => 'Guam', 'code' => '+1'),
    'gt' => array('country' => 'Guatemala', 'code' => '+502'),
    'gn' => array('country' => 'Guinea', 'code' => '+224'),
    'gw' => array('country' => 'Guinea-Bissau', 'code' => '+245'),
    'gy' => array('country' => 'Guyana', 'code' => '+592'),
    'ht' => array('country' => 'Haiti', 'code' => '+509'),
    'hn' => array('country' => 'Honduras', 'code' => '+504'),
    'hk' => array('country' => 'Hong Kong', 'code' => '+852'),
    'hu' => array('country' => 'Hungary', 'code' => '+36'),
    'is' => array('country' => 'Iceland', 'code' => '+354'),
    'in' => array('country' => 'India', 'code' => '+91'),
    'id' => array('country' => 'Indonesia', 'code' => '+62'),
    'ir' => array('country' => 'Iran', 'code' => '+98'),
    'iq' => array('country' => 'Iraq', 'code' => '+964'),
    'ie' => array('country' => 'Ireland', 'code' => '+353'),
    'il' => array('country' => 'Israel', 'code' => '+972'),
    'it' => array('country' => 'Italy', 'code' => '+39'),
    'ci' => array('country' => 'Ivory Coast', 'code' => '+225'),
    'jm' => array('country' => 'Jamaica', 'code' => '+1'),
    'jp' => array('country' => 'Japan', 'code' => '+81'),
    'jo' => array('country' => 'Jordan', 'code' => '+962'),
    'kz' => array('country' => 'Kazakhstan', 'code' => '+7'),
    'ke' => array('country' => 'Kenya', 'code' => '+254'),
    'ki' => array('country' => 'Kiribati', 'code' => '+686'),
    'kw' => array('country' => 'Kuwait', 'code' => '+965'),
    'kg' => array('country' => 'Kyrgyzstan', 'code' => '+996'),
    'la' => array('country' => 'Laos', 'code' => '+856'),
    'lv' => array('country' => 'Latvia', 'code' => '+371'),
    'lb' => array('country' => 'Lebanon', 'code' => '+961'),
    'ls' => array('country' => 'Lesotho', 'code' => '+266'),
    'lr' => array('country' => 'Liberia', 'code' => '+231'),
    'ly' => array('country' => 'Libya', 'code' => '+218'),
    'li' => array('country' => 'Liechtenstein', 'code' => '+423'),
    'lt' => array('country' => 'Lithuania', 'code' => '+370'),
    'lu' => array('country' => 'Luxembourg', 'code' => '+352'),
    'mo' => array('country' => 'Macau', 'code' => '+853'),
    'mk' => array('country' => 'Macedonia', 'code' => '+389'),
    'mg' => array('country' => 'Madagascar', 'code' => '+261'),
    'mw' => array('country' => 'Malawi', 'code' => '+265'),
    'my' => array('country' => 'Malaysia', 'code' => '+60'),
    'mv' => array('country' => 'Maldives', 'code' => '+960'),
    'ml' => array('country' => 'Mali', 'code' => '+223'),
    'mt' => array('country' => 'Malta', 'code' => '+356'),
    'mh' => array('country' => 'Marshall Islands', 'code' => '+692'),
    'mq' => array('country' => 'Martinique', 'code' => '+596'),
    'mr' => array('country' => 'Mauritania', 'code' => '+222'),
    'mu' => array('country' => 'Mauritius', 'code' => '+230'),
    'yt' => array('country' => 'Mayotte', 'code' => '+269'),
    'mx' => array('country' => 'Mexico', 'code' => '+52'),
    'fm' => array('country' => 'Micronesia, Federated States of', 'code' => '+691'),
    'md' => array('country' => 'Moldova', 'code' => '+373'),
    'mc' => array('country' => 'Monaco', 'code' => '+377'),
    'mn' => array('country' => 'Mongolia', 'code' => '+976'),
    'me' => array('country' => 'Montenegro', 'code' => '+382'),
    'ms' => array('country' => 'Montserrat', 'code' => '+1'),
    'ma' => array('country' => 'Morocco', 'code' => '+212'),
    'mz' => array('country' => 'Mozambique', 'code' => '+258'),
    'mm' => array('country' => 'Myanmar', 'code' => '+95'),
    'na' => array('country' => 'Namibia', 'code' => '+264'),
    'nr' => array('country' => 'Nauru', 'code' => '+674'),
    'np' => array('country' => 'Nepal', 'code' => '+977'),
    'nl' => array('country' => 'Netherlands', 'code' => '+31'),
    'an' => array('country' => 'Netherlands Antilles', 'code' => '+599'),
    'nc' => array('country' => 'New Caledonia', 'code' => '+687'),
    'nz' => array('country' => 'New Zealand', 'code' => '+64'),
    'ni' => array('country' => 'Nicaragua', 'code' => '+505'),
    'ne' => array('country' => 'Niger', 'code' => '+227'),
    'ng' => array('country' => 'Nigeria', 'code' => '+234'),
    'nu' => array('country' => 'Niue', 'code' => '+683'),
    'nf' => array('country' => 'Norfolk Island', 'code' => '+672'),
    'kp' => array('country' => 'North Korea', 'code' => '+850'),
    'mp' => array('country' => 'Northern Mariana Islands', 'code' => '+1'),
    'no' => array('country' => 'Norway', 'code' => '+47'),
    'om' => array('country' => 'Oman', 'code' => '+968'),
    'pk' => array('country' => 'Pakistan', 'code' => '+92'),
    'pw' => array('country' => 'Palau', 'code' => '+680'),
    'ps' => array('country' => 'Palestine', 'code' => '+970'),
    'pa' => array('country' => 'Panama', 'code' => '+507'),
    'pg' => array('country' => 'Papua New Guinea', 'code' => '+675'),
    'py' => array('country' => 'Paraguay', 'code' => '+595'),
    'pe' => array('country' => 'Peru', 'code' => '+51'),
    'ph' => array('country' => 'Philippines', 'code' => '+63'),
    'pl' => array('country' => 'Poland', 'code' => '+48'),
    'pt' => array('country' => 'Portugal', 'code' => '+351'),
    'pr' => array('country' => 'Puerto Rico', 'code' => '+1'),
    'qa' => array('country' => 'Qatar', 'code' => '+974'),
    'ro' => array('country' => 'Romania', 'code' => '+40'),
    'ru' => array('country' => 'Russia', 'code' => '+7'),
    'rw' => array('country' => 'Rwanda', 'code' => '+250'),
    'sh' => array('country' => 'Saint Helena', 'code' => '+290'),
    'kn' => array('country' => 'Saint Kitts and Nevis', 'code' => '+1'),
    'lc' => array('country' => 'Saint Lucia', 'code' => '+1'),
    'pm' => array('country' => 'Saint Pierre and Miquelon', 'code' => '+508'),
    'vc' => array('country' => 'Saint Vincent and the Grenadines', 'code' => '+1'),
    'ws' => array('country' => 'Samoa', 'code' => '+1'),
    'sm' => array('country' => 'San Marino', 'code' => '+378'),
    'st' => array('country' => 'Sao Tome and Principe', 'code' => '+239'),
    'sa' => array('country' => 'Saudi Arabia', 'code' => '+966'),
    'sn' => array('country' => 'Senegal', 'code' => '+221'),
    'rs' => array('country' => 'Serbia', 'code' => '+381'),
    'sc' => array('country' => 'Seychelles', 'code' => '+248'),
    'sl' => array('country' => 'Sierra Leone', 'code' => '+232'),
    'sg' => array('country' => 'Singapore', 'code' => '+65'),
    'sk' => array('country' => 'Slovakia', 'code' => '+421'),
    'si' => array('country' => 'Slovenia', 'code' => '+386'),
    'sb' => array('country' => 'Solomon Islands', 'code' => '+677'),
    'so' => array('country' => 'Somalia', 'code' => '+252'),
    'za' => array('country' => 'South Africa', 'code' => '+27'),
    'kr' => array('country' => 'South Korea', 'code' => '+82'),
    'es' => array('country' => 'Spain', 'code' => '+34'),
    'lk' => array('country' => 'Sri Lanka', 'code' => '+94'),
    'sd' => array('country' => 'Sudan', 'code' => '+249'),
    'sr' => array('country' => 'Suriname', 'code' => '+597'),
    'sz' => array('country' => 'Swaziland', 'code' => '+268'),
    'se' => array('country' => 'Sweden', 'code' => '+46'),
    'ch' => array('country' => 'Switzerland', 'code' => '+41'),
    'sy' => array('country' => 'Syria', 'code' => '+963'),
    'tw' => array('country' => 'Taiwan', 'code' => '+886'),
    'tj' => array('country' => 'Tajikistan', 'code' => '+992'),
    'tz' => array('country' => 'Tanzania', 'code' => '+255'),
    'th' => array('country' => 'Thailand', 'code' => '+66'),
    'tg' => array('country' => 'Togo', 'code' => '+228'),
    'tk' => array('country' => 'Tokelau', 'code' => '+690'),
    'to' => array('country' => 'Tonga', 'code' => '+676'),
    'tt' => array('country' => 'Trinidad and Tobago', 'code' => '+1'),
    'tn' => array('country' => 'Tunisia', 'code' => '+216'),
    'tr' => array('country' => 'Turkey', 'code' => '+90'),
    'tm' => array('country' => 'Turkmenistan', 'code' => '+993'),
    'tc' => array('country' => 'Turks and Caicos Islands', 'code' => '+1'),
    'tv' => array('country' => 'Tuvalu', 'code' => '+688'),
    'ug' => array('country' => 'Uganda', 'code' => '+256'),
    'ua' => array('country' => 'Ukraine', 'code' => '+380'),
    'ae' => array('country' => 'United Arab Emirates', 'code' => '+971'),
    'gb' => array('country' => 'United Kingdom', 'code' => '+44'),
    'us' => array('country' => 'United States', 'code' => '+1'),
    'uy' => array('country' => 'Uruguay', 'code' => '+598'),
    'vi' => array('country' => 'US Virgin Islands', 'code' => '+1'),
    'uz' => array('country' => 'Uzbekistan', 'code' => '+998'),
    'vu' => array('country' => 'Vanuatu', 'code' => '+678'),
    'va' => array('country' => 'Vatican City', 'code' => '+39'),
    've' => array('country' => 'Venezuela', 'code' => '+58'),
    'vn' => array('country' => 'Vietnam', 'code' => '+84'),
    'wf' => array('country' => 'Wallis and Futuna', 'code' => '+681'),
    'ye' => array('country' => 'Yemen', 'code' => '+967'),
    'zm' => array('country' => 'Zambia', 'code' => '+260'),
    'zw' => array('country' => 'Zimbabwe', 'code' => '+263'),
  );

  if (is_null($cc)) {
    return $country_code;
  }
  elseif (isset($country_code[$cc])) {
    return $country_code[$cc];
  }

  return FALSE;
}