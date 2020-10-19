#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int W = 1200, H = 1200, P = 100;
const int mask = (1 << 8) - 1;

double sqr(double a) {
	return a * a;
}

// calculations
bool isCovered(double x, double y) {
	bool f1 = -x / 3 + 1.0 / 3 <= y;
	bool f2 = 5 * x / 3 + 14.0 / 3 <= y;
	bool f3 = 0.96 * sqr(x) + 4.8 * x + 5 <= y;
	bool f4 = 0.96 * sqr(y) + 4.8 * y + 4 <= x;
	bool f5 = sqr(x + 2) + sqr(y - 2.5) <= 2.25;
	bool f6 = x >= -2.5 && x <= 1.5 && y <= -2.5 && y >= -4.5;
	bool f7 = 0.5 * abs(x - 3.5) + abs(y + 3.5) <= 1.5;
	bool res = false;
	res |= f4 && f6 && !f7;
	res |= !f2 && !f6 && !f4 && !f3 && x <= 0 && y <= 0;
	res |= !f2 && !f3 && !f5 && f1 && !f4;
	res |= f2 && !f3 && !f5 && f1 && !f4;
	return res;
}

pair<double, double> getXY(int i, int j) {
	double i0 = double(W) / 2;
	double j0 = double(H) / 2;
//	cout << x0 << ' ' << y0 << endl;
	pair<double, double> res;
	if (i <= i0) res.first = -((i0 - i) / P);
	else res.first = (i - i0) / P;
	if (j <= j0) res.second = (j0 - j) / P;
	else res.second = -((j - j0) / P);
	return res;
}
//

// drawing tools
void putPoint(RenderWindow &window, int x, int y, Color &color) {
	Vertex point(Vector2f(x, y), color);
	window.draw(&point, 1, Points);
}

void putLine(RenderWindow &window, int x1, int y1, int x2, int y2, Color color=Color::Black) {
	VertexArray line(Lines, 2);
	line[0].position = Vector2f(x1, y1);
	line[1].position = Vector2f(x2, y2);
	line[0].color = line[1].color = color;
	window.draw(line);
}
//

/*void _buildSquares(RenderWindow &window) {
	for (int i = 0; i < W; i += P)
		putLine(window, i, 0, i, H - 1);
	for (int j = 0; j < H; j += P)
		putLine(window, 0, j, W - 1, j);
	Color color = Color::Red;
	putLine(window, 0, H / 2, W - 1, H / 2, color);
	putLine(window, W / 2, 0, W / 2, H - 1, color);
}*/

// drawing main
void buildSquares(RenderWindow &window) {
	for (int i = W / 2; i >= 0; i -= P)
		putLine(window, i, 0, i, H - 1);
	for (int i = W / 2; i < W; i += P)
		putLine(window, i, 0, i, H - 1);
	for (int j = H / 2; j >= 0; j -= P)
		putLine(window, 0, j, W - 1, j);
	for (int j = H / 2; j < H; j += P)
		putLine(window, 0, j, W - 1, j);
	Color color = Color::Red;
	putLine(window, 0, H / 2, W - 1, H / 2, color);
	putLine(window, W / 2, 0, W / 2, H - 1, color);
}

void drugParty(RenderWindow &window) {
	for (int i = 0; i < W; ++i)
		for (int j = 0; j < H; ++j) {
			Color color = Color(rand() & mask, rand() & mask, rand() & mask);
			putPoint(window, i, j, color);
		}
}

void mainFill(RenderWindow &window) {
	for (int i = 0; i < W; ++i)
		for (int j = 0; j < H; ++j) {
			pair<double, double> cord = getXY(i, j);
			double x = cord.first, y = cord.second;
			Color color = Color::Cyan, color2 = Color::Black;
			if (isCovered(x, y)) putPoint(window, i, j, color);
		}
}

void filling(RenderWindow &window) {
	mainFill(window);
	buildSquares(window);
}
//

int main() {
	srand(time(NULL));
	freopen("consts.conf", "r", stdin);
	cin >> W >> H >> P;
	RenderWindow window(VideoMode(W, H), "Filler");
	Image icon;
	if (!icon.loadFromFile("icon.png")) return 1;
	window.setIcon(64, 64, icon.getPixelsPtr());
	int frames = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);
		filling(window);
		window.display();
		cout << "Frame " << ++frames << endl;
	}
}