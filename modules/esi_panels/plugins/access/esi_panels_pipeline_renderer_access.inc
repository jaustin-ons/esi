<?php
/**
 * @file
 * Plugin to provide access control to renderer pipelines.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Renderer access'),
  'description' => t('Control access to renderer pipelines.'),
  'callback' => 'esi_panels_pipeline_renderer_ctools_access_check',
  'default' => array(),
  'all contexts' => TRUE,
);

/**
 * Access check to control which ESI pipeline should be used.
 */
function esi_panels_pipeline_renderer_ctools_access_check($conf, $context, $plugin) {
  // Use debug_backtrace() to discover the display parameters.
  $trace = debug_backtrace();
  if ($trace[3]['function'] == 'panels_panel_context_render') {
    $handler = $trace[3]['args'][0];
  }

  // Discover the original intended pipeline, and find the ESI equivalent.
  if (isset($handler->conf['original_pipeline'])) {
    // $conf['pipeline'] will contain the name of the ESI pipeline being
    // tested: e.g. 'esi_ipe'.
    // The original pipeline should be in $conf['original_pipeline'].
    if ($conf['pipeline'] == 'esi_' . $handler->conf['original_pipeline']) {
      return TRUE;
    }
  }

  // The 'esi_standard' pipeline is always accessible, as this is the fallback
  // for any panels containing ESI panes.
  return $conf['pipeline'] == 'esi_standard';
}


