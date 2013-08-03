(function ($) {

  Drupal.behaviors.esi = {
    attach: function (context, settings) {
      $().esiTags().handleESI();
    }
  };

})(jQuery);
