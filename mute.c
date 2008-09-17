#define PURPLE_PLUGINS

#include <glib.h>

#include <plugin.h>
#include <version.h>

#include <signals.h>      // purple_signal_connect()
#include <account.h>      // PurpleAccount
#include <conversation.h> // purple_conversations_get_handle(),
                          // PurpleConversation

#include <ctype.h>        // tolower()

static gboolean
receiving_im_msg_cb(
    PurpleAccount *       account,
    char **               sender,
    char **               message,
    PurpleConversation *  conversation,
    PurpleMessageFlags *  flags,
    void * thunk
) {
  char *p;

  // convert the message to lowercase
  for (p = *message; *p; p++) {
    *p = tolower(*p);
  }

  return FALSE;
}

static gboolean
plugin_load(PurplePlugin *plugin) {

    // hook all im's before they're displayed
    purple_signal_connect(
        purple_conversations_get_handle(),
        "receiving-im-msg",
        plugin,
        PURPLE_CALLBACK( receiving_im_msg_cb ),
        NULL /* our thunk */);

    return TRUE;
}
static gboolean
plugin_unload(PurplePlugin *plugin) {

    purple_signal_disconnect(
        purple_conversations_get_handle(),
        "receiving-im-msg",
        plugin,
        PURPLE_CALLBACK( receiving_im_msg_cb ));

    return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION, PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL, 0, NULL,
    PURPLE_PRIORITY_DEFAULT,

    "core-mute",
    "Mute",
    "1.0",

    "Mutes incoming IMs by converting uppercase to lowercase.",
    "Mutes incoming IMs by converting uppercase to lowercase.",
    "Noah Easterly <noah@mailinator.com>",
    "http://rampion.blogspot.com",

    plugin_load,                   // our startup hook
    plugin_unload,                 // our shutdown hook
    NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

static void
init_plugin(PurplePlugin *plugin) { }

// magic macro that gets us run
PURPLE_INIT_PLUGIN(mute, init_plugin, info)
