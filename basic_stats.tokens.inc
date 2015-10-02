<?php

/**
 * @file
 * Token callbacks for the basic_stats module.
 */

/**
 * Implements hook_token_info().
 *
 */
function basic_stats_token_info() {
  $info['types']['basic-stats']         = array(
    'name'        => t('Basic stats'),
    'description' => t('Tokens related to Basic stats.'),
  );

  $info['tokens']['basic-stats']['nodes']   = array(
    'name'        => t('Node count'),
    'description' => t('The number of published nodes.'),
  );

  $content_types = node_type_get_names();
  foreach($content_types as $type => $name) {
    // Tokens for the basic statstoken type.
    $info['tokens']['basic-stats'][$type] = array(
      'name'        => t('Node count for @content_type', array('@content_type'=>$name)),
      'description' => t('The number of published @content_type nodes.', array('@content_type'=>$name)),
    );
  }

  $info['tokens']['basic-stats']['users']   = array(
    'name'        => t('User count'),
    'description' => t('Total of active users.'),
  );

  return $info;
}

  /**
* Implements hook_tokens().
*
* @ingroup token_example
*/
function basic_stats_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize     = !empty($options['sanitize']);

  // Text format tokens.
  if ($type == 'basic-stats') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'nodes':
          $replacements[$original] = basic_stats_number_nodes();
          break;

        case 'users':
          $replacements[$original] = basic_stats_number_users();
          break;

        default:
          $node_types = node_type_get_names();
          if(isset($node_types[$name])) {
            $replacements[$original] = basic_stats_number_nodes($name);
          }
          break;
      }
    }

  }
  return $replacements;
}