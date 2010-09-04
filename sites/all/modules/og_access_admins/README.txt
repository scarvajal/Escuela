/* $Id: README.txt,v 1.1 2010/04/13 13:24:19 gibus Exp $ */

-- SUMMARY --

The OG Access Admins module allows to restrict permissions to change
audience/visibility of posts belonging to a group to only
administrators of this group.

This feature to restrict access control to group admins only seems to
have been very often requested in og issues, see for eg. [#178811].
The OG Access Admins module provides a solution for this.

By default, with Organic groups, you can configure that visibility of
posts to be chosen by author/editor using a checkbox on the posting
form. The OG Access Admins module enhances this setup by allowing only
group administrators to change this visibility. To put it another way,
ordinary (non-admin) members of a group cannot change a private post
to be public, nor change a public post to be private, only group
admins can do this.

Also, by default with Organic groups, a post that does not belong to
any group is automatically set to be public. Therefore, another
outcome of the OG Access Admins module, is that only group admins are
allowed to change the audience of a post regarding the group(s) they
are admins of. This means that ordinary (non-admins) members of a
group do not see audience option for this group when editing a node.
Of course, for node creation, every members of a group can post in
this group.

Note that this means that even if Audience has been set up (in Organic
groups configuration) to be optional, every author (but node admins
and og admins) has to choose at least one group when creating a node.

Also, this module implies that members of a group, even this group
admins, cannot share a post belonging to this group with another group
if they are not administrator of this latest group. Conversely, an
administrator of a group can pull a post from another group he is
member of.


-- REQUIREMENTS --

Organic groups and OG Access module.


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

In Administer >> Organic groups >> Organic groups access
configuration, choose for "Audience/visibility of posts belonging to a
group can be changed by:", either "Any author/editor of the group"
(default behaviour of OG Access), or "This group administrators only"
(new behaviour allowed by OG Access Admins).

Note that this choice is only available if "Visibility of posts:" is
set to one of the "Visibility chosen by author/editor using a checkbox on the
posting form" options.


-- CONTACT --

Current maintainer:
* Gérald SÉDRATI-DINET - http://drupal.org/user/616006

This project has been sponsored by:
* SOPINSPACE
  One of the European reference solution providers for participatory democracy 
  and public debate using the Internet. Integrator of agile solutions 
  for Web-based collaborative work, including user support. Visit 
  http://www.sopinspace.com for more information.
