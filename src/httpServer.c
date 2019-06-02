
/* INCLUDES *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsoup/soup.h>
#include <assert.h>



/* CONSTANTS ******************************/
#define PORT_NUMBER 2222
#define SERVER_CREATION_ERR_MSG "Failed to create HTTP server\n"
#define SERVER_HEADER_STR "HTTP server daemon"
#define LISTEN_PORT_BOUND_ERR_MSG "Port could not be bound or other error occurred. Port number: %d\n"
#define PATH "/some-request"
#define URL_DELIMITER "/"
#define MIME_CONTENT_TYPE "text/html"



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
		return EXIT_FAILURE;
	}

	ssllResult = soup_server_listen_local(soupServer, PORT_NUMBER, 0,gError);
	if(FALSE == ssllResult)
	{
		g_print(LISTEN_PORT_BOUND_ERR_MSG, PORT_NUMBER);
		soup_server_disconnect(soupServer);
		return EXIT_FAILURE;
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
	char* token;
	guint32 respBodyLen;
	gpointer respBody;

	token = strtok((char*)path, URL_DELIMITER);
	token = strtok(NULL, URL_DELIMITER);
	if(NULL == token)
	{
		token = URL_DELIMITER;
	}

	respBodyLen = strlen(token) + 1;
	respBody = g_memdup(token, respBodyLen);

	soup_message_set_status(msg, SOUP_STATUS_OK);
	soup_message_set_response(msg, MIME_CONTENT_TYPE, SOUP_MEMORY_TAKE, respBody, respBodyLen);
}
