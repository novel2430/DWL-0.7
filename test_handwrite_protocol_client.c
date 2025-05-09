#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <wayland-client.h>
#include "handwrite-unstable-v1-protocol-client.h"

static struct zwp_handwrite_v1 *zwp_handwrite_v1 = NULL;

static void
registry_handle_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version)
{
	printf("interface: '%s', version: %d, name: %d\n",interface, version, name);
	if (strcmp(interface, zwp_handwrite_v1_interface.name) == 0) {
		printf("found handwrite interface in global\n");
        	zwp_handwrite_v1 = wl_registry_bind(registry, name, &zwp_handwrite_v1_interface, version);
		//zwp_handwrite_v1_send_handwrite_text(zwp_handwrite_v1, "好");
	}
}

static void
registry_handle_global_remove(void *data, struct wl_registry *registry,
		uint32_t name)
{
	// This space deliberately left blank
}

static const struct wl_registry_listener
registry_listener = {
	.global = registry_handle_global,
	.global_remove = registry_handle_global_remove,
};

int
main(int argc, char *argv[])
{
	struct wl_display *display = wl_display_connect(NULL);
        struct wl_registry *registry = wl_display_get_registry(display);

	wl_registry_add_listener(registry, &registry_listener, NULL);
	wl_display_dispatch(display);
	wl_display_roundtrip(display);
	zwp_handwrite_v1_send_handwrite_text(zwp_handwrite_v1, "好");
	wl_display_roundtrip(display);
	return 0;
}
