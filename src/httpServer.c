
/* INCLUDES *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <libsoup/soup.h>
#include <assert.h>


/* CONSTANTS ******************************/
#define PORT_NUMBER 2222
#define SERVER_CREATION_ERR_MSG "Failed to create HTTP server\n"
#define SERVER_HEADER_STR "HTTP server daemon"
#define LISTEN_PORT_BOUND_ERR_MSG "Port could not be bound or other error occurred.\n"
#define PATH "/"
#define SUCCESS_MSG "\n127.0.0.1:2222 was browsed"



/* FUNCTION DECLARATION (GLOBAL) *******************/
void callback(SoupServer *soupServer,
			  SoupMessage *msg,
			  const char *path,
			  GHashTable *query,
			  SoupClientContext *client,
			  gpointer user_data);



/* FUNCTION DEFINITION (GLOBAL) ********************/
int main(void) {

	SoupServer *soupServer;
	gboolean ssllResult;
	GError **gError = NULL;
	GMainLoop *gMainLoop;


	soupServer = soup_server_new(SOUP_SERVER_SERVER_HEADER, SERVER_HEADER_STR, NULL);
	if(NULL == soupServer)
	{
		g_print(SERVER_CREATION_ERR_MSG);
	}

	ssllResult = soup_server_listen_local(soupServer, PORT_NUMBER, 0,gError);
	if(FALSE == ssllResult)
	{
		g_print(LISTEN_PORT_BOUND_ERR_MSG);
	}

	soup_server_add_handler(soupServer, PATH, callback, NULL, NULL);

	gMainLoop = g_main_loop_new(NULL,FALSE);
	g_main_loop_run(gMainLoop);

	return EXIT_SUCCESS;
}



void callback(SoupServer *soupServer,
			  SoupMessage *msg,
			  const char *path,
			  GHashTable *query,
			  SoupClientContext *client,
			  gpointer user_data)
{
	g_print(SUCCESS_MSG);
}
