// $Id: og_access_admins.js,v 1.1 2010/04/13 13:24:19 gibus Exp $
/* Disable og_admins_control if og_visibility is set to always private or always public.
 */
Drupal.behaviors.og_access_admin_settings = function() {
  $("input[Name='og_visibility']").click(function() {
    if ($("input[Name='og_visibility']:checked").val() < 2) {
      $("input[name='og_admins_control']").attr('disabled','disabled');
    }
    else {
      $("input[name='og_admins_control']").removeAttr('disabled');
    }
  });

  // Set initial value.
  if ($("input[Name='og_visibility']:checked").val() < 2) {
    $("input[name='og_admins_control']").attr('disabled','disabled');
  }
  else {
    $("input[name='og_admins_control']").removeAttr('disabled');
  }
};
