const http = require('http');

const hostname = '0.0.0.0';
const port = process.env.PORT || 8080;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  var response_str = get_html_response();
  res.end(response_str);
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});


function get_html_response()
{
	var response = '{ "appname" : "Web Server", "Version" : "1.0", "Build Date: 02/27/2019" }';
	return response;
}
