#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Entity.h"
#include "Ship.h"
#include "Stern.h"
#include "Bullet.h"
#include "Rocket.h"
#include "UFO.h"
#include "Tank.h"
#include "Asteroid.h"
#include "Snip.h"
using namespace sf;


#include <list>
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//#include <windows.h>
//
//#pragma comment (lib, "kernel32.lib")
//#pragma comment (lib, "user32.lib")
//#pragma comment (lib, "ole32.lib")
//
//#pragma comment (lib, "gdi32.lib")
//#pragma comment (lib, "msvcrt.lib")
//#pragma comment (linker, "/subsystem:windows /entry:mainCRTStartup")
//
//
//char keyboard[256] = { 0 };
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
//{
//	switch (message)
//	{
//	case WM_KEYUP:
//		keyboard[wparam] = 0;
//		break;
//	case WM_KEYDOWN:
//		keyboard[wparam] = 1;
//		break;
//	case WM_DESTROY:
//		keyboard[VK_ESCAPE] = 1;
//		break;
//	default:
//		break;
//	}
//	return DefWindowProc(hwnd, message, wparam, lparam);
//}

///////////////////////////////////////////////////////////////////////////////////////////////

bool isCollide(Entity *a, Entity *b, int R1, int R2)
{
	return (b->OldX - a->OldX)*(b->OldX - a->OldX) +
		(b->OldY - a->OldY)*(b->OldY - a->OldY) <
		(R1 + R2)*(R1 + R2);
}

float AIinPutX(int x1, int y1, int x2, int y2)
{
	int x_unit = 1, Dx = x2 - x1, Dy = y2 - y1; // Init first value
	int x = x1;
	float y = y1;
	float y_unit = 1;

	if (Dx < 0)
		x_unit = -1;
	if (Dy < 0)
		y_unit = -1;

	if (x1 == x2)   // duong thang dung
	{
		x_unit = 0;
	}
	else if (y1 == y2)  // duong ngang
	{
		y_unit = 0;
	}
	else if (x1 != x2 && y1 != y2)// duong xien
	{
		float m = (float)abs(Dy) / abs(Dx);
		x_unit = 1;
		y_unit = m;
		x = x1;
		y = y1;

		if (Dx < 0)
			x_unit = -1;        // ve x giam
		if (Dy < 0)
			y_unit = -m;        // ve y giam
	}
	return x_unit;
}

float AIinPutY(int x1, int y1, int x2, int y2)        // DDA algorithm
{
	int x_unit = 1, Dx = x2 - x1, Dy = y2 - y1;
	int x = x1;
	float y = y1;
	float y_unit = 1;

	if (Dx < 0)
		x_unit = -1;
	if (Dy < 0)
		y_unit = -1;

	if (x1 == x2)   // duong thang dung
	{
		x_unit = 0;
	}
	else if (y1 == y2)  // duong ngang
	{
		y_unit = 0;
	}
	else if (x1 != x2 && y1 != y2)// duong xien
	{
		float m = (float)abs(Dy) / abs(Dx);
		x_unit = 1;
		y_unit = m;
		x = x1;
		y = y1;

		if (Dx < 0)
			x_unit = -1;        // ve x giam
		if (Dy < 0)
			y_unit = -m;        // ve y giam
	}
	return y_unit;
}

float kc(float ax, float ay, float bx, float by)//tính khoảng cách giửa 2 điểm
{
	float kx, ky;
	kx = ax - bx;
	ky = ay - by;
	return sqrt(kx*kx + ky*ky);
}

float Angle(float ax, float ay, float bx, float by, float cx, float cy)
{
	float xAB, yAB, xAC, yAC;
	xAB = bx - ax; yAB = by - ay;
	xAC = cx - ax; yAC = cy - ay;
	float a, b;
	a = xAB*xAC + yAB*yAC;
	b = kc(ax, ay, bx, by)*kc(ax, ay, cx, cy);
	float c = acos((a / b)) * 180.0 / 3.14;
	if (cy < ay)
		return 360 - c;
	else
		return c;
}

void SetMusicEvent(sf::Music &MusicEvent, std::string File, int volume)
{
	MusicEvent.openFromFile(File);
	MusicEvent.setVolume(volume);
	MusicEvent.play();
}

int HidenBoss(RenderWindow &app);
//////Menu///////////////////
int Menu(RenderWindow &app, int x, int y);
int Start(RenderWindow &app);

int HidenBoss(RenderWindow &app)
{
	app.setMouseCursorVisible(true);
	Texture tBoss;
	tBoss.loadFromFile("images/earth.png");
	Sprite sBoss(tBoss);
	while (app.isOpen())
	{
		app.clear();
		app.draw(sBoss);
		app.display();
		
	}
	return 0;
}


int Menu(RenderWindow &app, int x, int y)
{

	app.setMouseCursorVisible(true);

	Texture tbackgrounp, tabout, tScore, tWin, tDeaf;
	tbackgrounp.loadFromFile("images/Menu.png");
	Sprite background(tbackgrounp);
	background.setPosition(x, y);
	tabout.loadFromFile("images/about.png");
	Sprite about(tabout);
	about.setPosition(1921 + x, 230 + y);
	/*tScore.loadFromFile("images/Score.png");
	Sprite Score(tScore);
	tWin.loadFromFile("images/thang.png");
	Sprite Win(tWin);
	Win.setPosition(0, 0);
	tDeaf.loadFromFile("images/Thua.png");
	Sprite Deaf(tDeaf);
	Deaf.setPosition(0, 0);*/

	int i = 0, click = 0;
	bool check = false;
	//Start the game loop
	while (app.isOpen())
	{
		// Process events
		sf::Event event;
		while (app.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				app.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				if (Mouse::getPosition().x > 220 && Mouse::getPosition().x < 410 && Mouse::getPosition().y > 480 && Mouse::getPosition().y < 550)
				{
					Start(app);
				}
				if (Mouse::getPosition().x > 200 && Mouse::getPosition().x < 450 && Mouse::getPosition().y > 610 && Mouse::getPosition().y < 670)
				{
					check = true;
				}
				if (Mouse::getPosition().x > 240 && Mouse::getPosition().x < 400 && Mouse::getPosition().y > 740 && Mouse::getPosition().y < 820)
				{
					app.close();
				}
			}
		}

		if (check == true)
		{
			i += 4;
			if (i == 1200)
			{
				i = 1200;
				check = false;
			}
		}
		about.setPosition(1921 - i + x, 230 + y);
		app.clear();
		app.draw(background);
		//window.draw(Deaf);
		app.draw(about);
		app.display();
	}
	return 0;
}

int main(int argc, char * argv[])
{

	///////////////////////////////////////////////////////////////////////////////////

	/*MSG msg;
	static TCHAR appname[] = TEXT("Demo");
	WNDCLASS wc = { 0 };

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = appname;
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_3DFACE + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Cannot register class"), TEXT("Error"), MB_ICONERROR | MB_OK);
		return -1;
	}*/

	///////////////////////////////////////////////////////////////////////////////////




	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SpaceShip");

	sf::Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		Menu(window, 0, 0);
		window.clear();
		window.display();
	}
	return 0;
}

int Start(RenderWindow &app)
{
	srand(time(0));

	//hide mouse;
	app.setMouseCursorVisible(false);

	// app(VideoMode(1920, 1080), "Asteroids!");
	app.setFramerateLimit(60);

	sf::View view; //= app.getView();
	view.setSize(1920, 1080);

	Texture tShip, tBullet_Ship, tRocket_Ship, tBlood_Ship, tIconBlood, thealth, tbullet, tHoimau;
	tShip.loadFromFile("images/spaceship3.png");
	Animation sPlayer(tShip, 0, 0, 65, 100, 1, 0);
	Animation sPlayer_go(tShip, 65, 0, 65, 100, 1, 0.5);
	tBullet_Ship.loadFromFile("images/Bullet_Ship.png");
	Animation sBullet(tBullet_Ship, 0, 0, 20, 80, 3, 0.5);
	tRocket_Ship.loadFromFile("images/RocKet_Ship.png");
	Animation sRocket(tRocket_Ship, 0, 0, 20, 100, 3, 0.5);
	tBlood_Ship.loadFromFile("images/blood.png");
	Sprite Blood;
	Blood.setTexture(tBlood_Ship);
	tIconBlood.loadFromFile("images/Iconblood.png");
	Animation sIconBlood(tIconBlood, 0, 0, 50, 100, 2, 0.05);
	thealth.loadFromFile("images/Health.png");
	Animation sIconHealth(thealth, 0, 0, 100, 100, 1, 0);
	tbullet.loadFromFile("images/iconBullet.png");
	Animation sIconbullet(tbullet, 0, 0, 50, 50, 2, 0.05);
	tHoimau.loadFromFile("images/hoimau.png");
	Animation sHoimau(tHoimau, 0, 0, 300, 200, 29, 0.2);

	///SCORE////////////////////////SCORE///////////////
	int Score = 0;

	Font font;
	font.loadFromFile("images/arial.ttf");


	///////Background/////ICON////////
	Texture tBackground, tUI, tIconTime, tMouse, tScore, tWin, tDeaf, tbackground, tabout, tTimewait;
	tBackground.loadFromFile("images/background.png");
	Sprite background(tBackground);
	tUI.loadFromFile("images/UI.png");
	Sprite UI(tUI);
	tIconTime.loadFromFile("images/iconTime.png");
	Sprite iconTime_k(tIconTime);
	Sprite iconTime_r(tIconTime);
	tMouse.loadFromFile("images/mouse.png");
	Sprite IconMouse(tMouse);

	tScore.loadFromFile("images/Score.png");
	Sprite sscore(tScore);
	tWin.loadFromFile("images/thang.png");
	Sprite Win(tWin);
	tDeaf.loadFromFile("images/Thua.png");
	Sprite Deaf(tDeaf);
	tTimewait.loadFromFile("images/timewait.png");
	Animation sTimewait(tTimewait, 0, 0, 60, 60, 13, 0.05);



	////////Effect///////////////
	Texture tEffect_C, tWebSprite, DestroyShip, DestroyUFO;
	tEffect_C.loadFromFile("images/explosions/type_C.png");
	Animation sExplosion(tEffect_C, 0, 0, 256, 256, 48, 0.5);
	tWebSprite.loadFromFile("images/webspite.png");
	Animation sWebSpite(tWebSprite, 0, 0, 100, 100, 15, 0.2);
	DestroyShip.loadFromFile("images/explosions/type_B.png");
	Animation sExplosion_ship(DestroyShip, 0, 0, 192, 192, 64, 0.5);
	DestroyUFO.loadFromFile("images/explosions/type_A.png");
	Animation sExplosion_UFO(DestroyUFO, 0, 0, 51, 50, 20, 1);
	//t4.loadFromFile("images/rock.png");

	//t6.loadFromFile("images/rock_small.png");

	//////////////UFO/////////////////////
	Texture tUFO1, tUFO2, tUFO3, tUFO31, tBullet_UFO1, tBullet_UFO3, tBullet_UFO2;
	tUFO1.loadFromFile("images/UFO1.png");
	Animation sUFO1(tUFO1, 0, 0, 120, 120, 1, 0);
	tUFO2.loadFromFile("images/UFO2.png");
	Animation sUFO2(tUFO2, 0, 0, 120, 120, 5, 0.01);
	tUFO3.loadFromFile("images/UFO3.png");
	Animation sUFO3(tUFO3, 0, 0, 100, 120, 1, 0);
	tUFO31.loadFromFile("images/UFO31.png");
	Animation sUFO31(tUFO31, 0, 0, 50, 60, 1, 0);
	tBullet_UFO3.loadFromFile("images/Bullet_UFO3.png");
	Animation sBullet_UFO3(tBullet_UFO3, 0, 0, 50, 50, 1, 0);
	tBullet_UFO1.loadFromFile("images/Bullet_UFO1.png");
	Animation sBullet_UFO1(tBullet_UFO1, 0, 0, 30, 100, 2, 0.5);
	tBullet_UFO2.loadFromFile("images/Bullet_Magic_green.png");
	Animation sBullet_UFO2(tBullet_UFO2, 0, 0, 32, 85, 4, 0.5);

	////////////Tank//////////////////
	Texture tTank;
	tTank.loadFromFile("images/tank1.png");
	Animation sTank(tTank, 0, 0, 160, 200, 20, 0.3);

	Texture tBoss, tboss1, tboss2, tboss3;
	tBoss.loadFromFile("images/earth.png");
	tboss1.loadFromFile("images/Bullet_UFO3.png");
	Sprite sBoss(tBoss);
	sBoss.setPosition(5000, 0);
	Animation sboss1(tboss1, 0, 0, 1, 1, 1, 0);
	Animation sboss2(tboss1, 0, 0, 1, 1, 1, 0);
	Animation sboss3(tboss1, 0, 0, 1, 1, 1, 0);

	Texture tBlood_Boss;
	tBlood_Boss.loadFromFile("images/bloodboss.png");
	Sprite BloodBoss;
	BloodBoss.setTexture(tBlood_Boss);



	tShip.setSmooth(true);
	tBackground.setSmooth(true);

	Texture t6, t4;
	t6.loadFromFile("images/rock_small.png");
	t4.loadFromFile("images/rock.png");
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);

	//Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
	//Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);

	//Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
	//Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);

	//Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

	Texture tSnip;
	tSnip.loadFromFile("images/Snip.png");
	Animation sSnip(tSnip, 0, 0, 60, 60, 1, 0);

	//5760 x 3240



	sf::Music musicGame, musicGun, musicUFODestroy, musicShipDestroy, musicShip, musicMyRocket, mucsicMyBullet, musicHealth, musicBlood, musicMyRocket_UFO, musicYourBullet_Ship, musicMyBullet_UFO, musicYourRocket, musicShipFly, musicIconBullet;
	musicUFODestroy.openFromFile("images/Sound/UFO_Die.wav");
	musicShipDestroy.openFromFile("images/Sound/SpaceDestroy.wav");
	musicGame.openFromFile("images/Sound/gamemusic.ogg");
	musicMyRocket.openFromFile("images/Sound/myrocket.wav");
	mucsicMyBullet.openFromFile("images/Sound/mybullet.wav");
	musicHealth.openFromFile("images/Sound/Health.wav");
	musicBlood.openFromFile("images/Sound/blood.wav");
	musicMyRocket_UFO.openFromFile("images/Sound/myRocket_Vacham_UFO.wav");
	musicYourBullet_Ship.openFromFile("images/Sound/miss_hit.wav");
	musicMyBullet_UFO.openFromFile("images/Sound/VaCham.wav");
	musicYourRocket.openFromFile("images/Sound/yourrocket.wav");
	musicShipFly.openFromFile("images/Sound/engine_loop.wav");
	musicIconBullet.openFromFile("images/Sound/IconBullet.wav");

	musicGame.play();
	musicGame.setVolume(30);

	std::list<Entity*> entities;

	Ship *p = new Ship();
	p->settings(sPlayer, 800, 800, 20);
	entities.push_back(p);

	Ship *Sn = new Snip();
	Sn->settings(sSnip, p->OldX + 60, p->OldY + 15, 20);
	entities.push_back(Sn);


	for (int i = 0; i<15; i++)
	{
		Asteroid *a = new Asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
	}

	for (int i = 0; i < 10; i++)
	{
		UFO *a = new UFO();
		if (i % 2 == 0)
			a->settings(sUFO3, rand() % 1000 + 5000, rand() % 500 + 0, (rand() % 5 + 2) * 10, 700, rand() % 360, 3, 3);
		else
			a->settings(sUFO2, rand() % 1000 + 5000, rand() % 500 + 0, (rand() % 5 + 2) * 10, 500, rand() % 360, 2, 2);

		entities.push_back(a);
	}

	view.setCenter(p->OldX, p->OldY);

	float youngX, youngY;//line 254
	float Time_wait = 20, Frame_Tank = 20, Frame_Rocket = 10, Frame_HoiMau = 10, Frame_kill = 0, timeSpeed = 0;
	bool check = true;
	int ShowScore = 0;
	bool ShowMenu = false, hoimau = false, boss = false;
	int AmountBullet = 4, kill = 1, bloodboss = 0, Minute = 4, Second = 10;

	/////main loop/////
	while (app.isOpen())
	{
		Event event;

		Frame_Tank += 0.05;
		Frame_Rocket += 0.01;
		Frame_HoiMau += 0.05;
		Frame_kill += 0.01;
		//cout << Frame_Tank << endl;
		//musicGame.play();
		musicGame.setLoop(true);

		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left && ShowMenu == true)
				{
					if (Mouse::getPosition().x + UI.getPosition().x > UI.getPosition().x + 850 && Mouse::getPosition().x + UI.getPosition().x < 1070 + UI.getPosition().x && Mouse::getPosition().y + UI.getPosition().y > UI.getPosition().y + 820 && Mouse::getPosition().y + UI.getPosition().y < 1000 + UI.getPosition().y)
					{
						musicGame.stop();
						Menu(app, UI.getPosition().x, UI.getPosition().y);
						//cout << "Menu" << endl;
					}


				}
				if (event.key.code == sf::Mouse::Left)
				{
					if (AmountBullet < 2)
					{
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle, 1);
						entities.push_back(c);
					}
					else if (AmountBullet < 3)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 3, 1);
						entities.push_back(d);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 3, 1);
						entities.push_back(b);
					}
					else if (AmountBullet < 4)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 5, 1);
						entities.push_back(d);
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle, 1);
						entities.push_back(c);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 5, 1);
						entities.push_back(b);
					}
					else if (AmountBullet < 5)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 15, 1);
						entities.push_back(d);
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle - 4, 1);
						entities.push_back(c);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 4, 1);
						entities.push_back(b);
						Bullet *a = new Bullet();
						a->settings(sBullet, p->OldX, p->OldY, p->Angle + 15, 1);
						entities.push_back(a);
					}

					else if (AmountBullet < 6)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 15, 1);
						entities.push_back(d);
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle - 5, 1);
						entities.push_back(c);
						Bullet *e = new Bullet();
						e->settings(sBullet, p->OldX, p->OldY, p->Angle, 1);
						entities.push_back(e);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 5, 1);
						entities.push_back(b);
						Bullet *a = new Bullet();
						a->settings(sBullet, p->OldX, p->OldY, p->Angle + 15, 1);
						entities.push_back(a);
					}
					else if (AmountBullet < 7)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 15, 1);
						entities.push_back(d);
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle - 7, 1);
						entities.push_back(c);
						Bullet *e = new Bullet();
						e->settings(sBullet, p->OldX, p->OldY, p->Angle + 4, 1);
						entities.push_back(e);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 7, 1);
						entities.push_back(b);
						Bullet *a = new Bullet();
						a->settings(sBullet, p->OldX, p->OldY, p->Angle + 15, 1);
						entities.push_back(a);
						Bullet *f = new Bullet();
						f->settings(sBullet, p->OldX, p->OldY, p->Angle - 4, 1);
						entities.push_back(f);
					}
					else if (AmountBullet < 8)
					{
						Bullet *d = new Bullet();
						d->settings(sBullet, p->OldX, p->OldY, p->Angle - 20, 1);
						entities.push_back(d);
						Bullet *c = new Bullet();
						c->settings(sBullet, p->OldX, p->OldY, p->Angle - 10, 1);
						entities.push_back(c);
						Bullet *e = new Bullet();
						e->settings(sBullet, p->OldX, p->OldY, p->Angle + 5, 1);
						entities.push_back(e);
						Bullet *b = new Bullet();
						b->settings(sBullet, p->OldX, p->OldY, p->Angle + 20, 1);
						entities.push_back(b);
						Bullet *a = new Bullet();
						a->settings(sBullet, p->OldX, p->OldY, p->Angle + 10, 1);
						entities.push_back(a);
						Bullet *f = new Bullet();
						f->settings(sBullet, p->OldX, p->OldY, p->Angle - 5, 1);
						entities.push_back(f);
						Bullet *h = new Bullet();
						h->settings(sBullet, p->OldX, p->OldY, p->Angle, 1);
						entities.push_back(h);
					}

					mucsicMyBullet.play();
					mucsicMyBullet.setVolume(25);

					/*for (int i = 0; i < AmountBullet; i++)
					{
						Bullet *b = new Bullet();
						b->settings(sBullet, (p->OldX - 40) + 20 * i, (p->OldY - 40) + 20 * i, (p->Angle - 6) + 3 * i, 1);
						entities.push_back(b);
					}*/



					//SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 40);
				}

				if (event.key.code == sf::Mouse::Right)
				{
					if (Frame_Rocket >= Time_wait)
					{
						Rocket *r = new Rocket();
						r->settings(sRocket, p->OldX, p->OldY, p->Angle, 1);
						entities.push_back(r);
						Frame_Rocket = kill * 3;
						//SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 40);
						Tank *time = new Tank();
						time->settings(sTimewait, view.getCenter().x + 320 + 30, view.getCenter().y + 431 + 30, -90, 3);
						entities.push_back(time);
						musicMyRocket.play();
					}
				}
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left)
				{
					if (Frame_Tank >= Time_wait)
					{
						Tank *t = new Tank();
						t->settings(sTank, p->OldX, p->OldY, p->Angle, 0);
						entities.push_back(t);
						Frame_Tank = 4 * kill;
						//hoimau = true;
						//SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 40);
						Tank *time = new Tank();
						time->settings(sTimewait, view.getCenter().x - 282 + 30, view.getCenter().y + 431 + 30, -90, 2);
						entities.push_back(time);
					}
				}
			}
		}

		app.setView(view);
		//view.setPosition(p->OldX - 960, p->OldY - 540);

		//lấy tọa độ chuột
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			youngX = sf::Mouse::getPosition().x; youngY = sf::Mouse::getPosition().y;
			p->Angle = Angle(W / 2, H / 2, W / 2 + 10, H / 2, youngX, youngY);


			//Sn->Angle = p->Angle;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && check == true)
		{
			p->thrust = true;

			//musicShip.setLoop(true);
		}
		else
		{
			p->thrust = false;
			//musicShipFly.stop();
		}

		if (hoimau)
		{
			Tank *t = new Tank();
			t->settings(sHoimau, p->OldX, p->OldY, -90, 1);
			entities.push_back(t);
			musicBlood.play();
			musicBlood.setVolume(25);
			hoimau = false;
			//Frame_Tank = 20;
		}

		p->frame_Ship += 0.1;
		if (p->frame_Ship >= p->time_Ship)
		{
			check = true;
			//musicShipFly.play();
			p->frame_Ship = 0;
		}
		if (p->life == true)
		{
			view.setCenter(p->OldX, p->OldY);
		}
		else
			view.setCenter(1920 / 2, 1080 / 2);

		///////UI////////////UI////////
		UI.setPosition(view.getCenter().x - 960, view.getCenter().y - 540);

		//////////////////////////////////////////SNIP////////////////////
		Sn->OldX = p->OldX + 60;
		Sn -> OldY = p->OldY + 10 ;
		
		///////////////////////////////////////////////

		if (Score > 5000)
		{
			if (Minute <= 0 && Second <= 1)
			{
				timeSpeed += 0;
				Second = 0;
				ShowScore = 1;
			}
			else
				timeSpeed += 0.1;
			if (timeSpeed >= 6)
			{
				Second--;
				timeSpeed = 0;
				if (Second <= 0)
				{
					Minute--;
					Second = 59;
					if (Minute <= 0 && Second <= 0)
					{
						ShowScore = 1;
					}
				}	
			}
		}



		////update location score
		Text text(std::to_string(Score), font, 50), health(std::to_string(p->Health), font, 50), textminute(std::to_string(Minute) + ": ", font, 50), textSecond(std::to_string(Second), font, 50);
		text.setPosition(1650 + UI.getPosition().x, 20 + UI.getPosition().y);
		text.setColor(Color::Red);
		health.setPosition(view.getCenter().x + 20, view.getCenter().y + 390);
		health.setColor(Color::Yellow);
		textminute.setPosition(view.getCenter().x - 30, view.getCenter().y - 510);
		textminute.setColor(Color::Yellow);
		textSecond.setPosition(view.getCenter().x + 30, view.getCenter().y - 510);
		textSecond.setColor(Color::Yellow);
		//////
		sscore.setPosition(UI.getPosition().x, UI.getPosition().y);
		Deaf.setPosition(UI.getPosition().x, UI.getPosition().y);
		Win.setPosition(UI.getPosition().x, UI.getPosition().y);


		//lấy tọa độ chuột theo view
		IconMouse.setPosition(sf::Mouse::getPosition().x - 25 + view.getCenter().x - 960, sf::Mouse::getPosition().y - 25 + view.getCenter().y - 540);

		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "Tank")
				{
					if (a->Species == 0)
					{
						//a->frame_Tank += 0.01;
						//cout << a->frame_Tank << endl;
						if (Frame_Tank >= Time_wait)
						{
							a->life = false;
							Frame_Tank = 0;

						}
						a->Angle = p->Angle;
						a->OldX = view.getCenter().x;;
						a->OldY = view.getCenter().y;
					}
					if (a->Species == 1)
					{
						if (Frame_HoiMau >= Time_wait)
						{
							a->life = false;
							Frame_HoiMau = 10;
						}
						a->Angle == -90;
						a->OldX = view.getCenter().x;;
						a->OldY = view.getCenter().y;
					}
					if (a->Species == 2)
					{
						if (Frame_Tank >= Time_wait)
						{
							a->life = false;
							//Frame_Tank = 0;
						}
						a->Angle = -90;
						a->OldX = view.getCenter().x - 282 + 30;
						a->OldY = view.getCenter().y + 431 + 30;
					}
					if (a->Species == 3)
					{
						if (Frame_Rocket >= Time_wait)
						{
							a->life = false;
							//Frame_Rocket = 0;
						}
						a->Angle == -90;
						a->OldX = view.getCenter().x + 320 + 30;
						a->OldY = view.getCenter().y + 431 + 30;
					}


				}

				if(a->name == "asteroid")
				{
					if (a->OldX <= 0 || a->OldX >= 6000 || a->OldY <= 0 || a->OldY >= 4000)
						a->life = false;
				}

				if (a->name == "Snip" && b->name == "UFO")
				{
					if (isCollide(Sn, b, b->R, Sn->R2_Ship))
					{
						Sn->Angle = Angle(Sn->OldX, Sn->OldY, Sn->OldX + 10, Sn->OldY, b->OldX, b->OldY);
						if (isCollide(a, b, b->R, a->R2_Ship))
						{
							Sn->frame_Ship += 0.05;
							if (Sn->frame_Ship >= Sn->time_Ship)
							{
								Bullet *d = new Bullet();
								d->settings(sBullet, Sn->OldX, Sn->OldY, Sn->Angle - 7, 1);
								entities.push_back(d);
								Bullet *c = new Bullet();
								c->settings(sBullet, Sn->OldX, Sn->OldY, Sn->Angle, 1);
								entities.push_back(c);
								Bullet *e = new Bullet();
								e->settings(sBullet, Sn->OldX, Sn->OldY, Sn->Angle + 7, 1);
								entities.push_back(e);

								Sn->frame_Ship = 3;
								mucsicMyBullet.play();
								mucsicMyBullet.setVolume(20);
							}
						}
					}
				}

				if (a->name == "Ship" && b->name == "asteroid")
				{
					if (isCollide(a, b, a->R, b->R))
					{
						b->life = false;
						a->Blood -= 8;
						if (a->Blood <= 0)
						{
							//ship destroy
							SetMusicEvent(musicShipDestroy, "images/Sound/SpaceDestroy.wav", 30);
							Entity *E = new Entity();
							E->settings(sExplosion_ship, a->OldX, a->OldY, 0, 0);
							E->name = "explosion";
							entities.push_back(E);

							p->settings(sPlayer, 800, 800, 20);
							p->Blood = 21;
							a->Health--;
							if (AmountBullet > 1)
								AmountBullet--;
							if (a->Health <= 0)
							{
								ShowScore = 1;
								p->R3_Ship = 0;
								p->R = 0;
								p->R2_Ship = 0;
								p->R1_Ship = 0;
								p->Health = 0;
							}
						}
					}
				}

				if (a->name == "UFO" && b->name == "asteroid")
				{
					if (a->Species == 1 || a->Species == 2, a->Species == 3 || a->Species || a->Species == 0)
					{
						if (isCollide(a, b, a->R, b->R))
						{
							a->life = false;
							b->life = false;
							Entity *e = new Entity();
							e->settings(sExplosion, b->OldX, b->OldY, 0, 0);
							e->name = "explosion";
							entities.push_back(e);
							musicUFODestroy.setVolume(10);
							musicUFODestroy.play();
						}
					}
				}

				if (a->name == "Bullet" && b->name == "asteroid")
				{
					if (isCollide(a, b, a->R, b->R))
					{
						b->Blood--;
						a->life = false;
						if (b->Blood <= 0)
						{
							b->life = false;
							if (b->R > 20)
							{
								for (int i = 0; i < 3; i++)
								{
									Asteroid *t = new Asteroid();
									t->settings(sRock_small, b->OldX, b->OldY, rand() % 360, 20);
									entities.push_back(t);
								}
							}
							Entity *e = new Entity();
							e->settings(sExplosion, b->OldX, b->OldY, 0, 0);
							e->name = "explosion";
							entities.push_back(e);
							musicUFODestroy.setVolume(10);
							musicUFODestroy.play();
						}
					}
				}

				if (a->name == "Stern")
				{
					if (a->OldX <= 0 || a->OldX >= 6000 || a->OldY <= 0 || a->OldY >= 4000)
						a->life = false;
				}

				if (a->name == "Bullet")
				{
					if (a->OldX <= 0 || a->OldX >= 6000 || a->OldY <= 0 || a->OldY >= 4000)
						a->life = false;
				}

				if (a->name == "Rocket")
				{
					if (a->OldX <= 0 || a->OldX >= 6000 || a->OldY <= 0 || a->OldY >= 4000)
						a->life = false;
				}

				if (a->name == "UFO" && b->name == "Tank")
				{
					if (a->Species == 1 || a->Species == 0 || a->Species == 2 || a->Species == 3)
					{
						if (isCollide(a, b, a->R, b->R) && b->Species == 0)
						{
							a->life = false;
							b->life = false;
						}
					}
				}

				if (a->name == "Bullet" && b->name == "Tank")
				{
					if (a->Species == 0 || a->Species == 2)
						if (isCollide(a, b, a->R, b->R))
							a->life = false;
				}

				if (a->name == "Rocket" && b->name == "Tank")
				{
					if (a->Species == 0)
						if (isCollide(a, b, a->R, b->R))
							a->life = false;
				}

				if (a->name == "UFO" && b->name == "Bullet")
				{
					if (b->Species == 1)
					{
						if (isCollide(a, b, a->R, b->R))
						{
							b->life = false;
							a->Blood--;
							musicMyBullet_UFO.play();
							musicMyBullet_UFO.setVolume(10);
							if (a->Blood <= 0)
							{
								if (a->Species == 4)
								{
									ShowScore = 2;
									//p->life = false;
									p->R3_Ship = 0;
									p->R = 0;
									p->R2_Ship = 0;
									p->R1_Ship = 0;
									p->Health = 0;
								}
								Score += 10;
								if (Score == 100)
								{
									cout << Score << endl;
									UFO *a = new UFO();
									a->settings(sboss1, 5500, 200, 200, 1700, 0, 4, 219);
									entities.push_back(a);
									UFO *b = new UFO();
									b->settings(sboss1, 5780, 100, 10, 1500, 0, 5, 100);
									entities.push_back(b);
									UFO *c = new UFO();
									c->settings(sboss1, 5700, 150, 10, 1500, 0, 6, 100);
									entities.push_back(c);
									Score += 10;
								}
								Entity *e = new Entity();
								e->settings(sExplosion, b->OldX, b->OldY, 0, 0);
								e->name = "explosion";
								entities.push_back(e);
								musicUFODestroy.setVolume(10);
								musicUFODestroy.play();
								if (a->R > 40 && a->Species == 3)
								{
									for (int i = 0; i < 2; i++)
									{
										UFO *u = new UFO();
										u->settings(sUFO31, b->OldX + rand() % 200, b->OldY + rand() % 200, 10 * (rand() % 2 + 2), 250, 20, 0, 2);
										entities.push_back(u);
									}
								}

								if (a->Species == 3)
								{
									if (a->R < 30)
									{
										Stern *s = new Stern();
										s->settings(sIconBlood, a->OldX, a->OldY, -90, 0);
										entities.push_back(s);
									}
								}
								if (a->Species == 1)
								{
									if (a->R > 50)
									{
										Stern *s = new Stern();
										s->settings(sIconHealth, a->OldX, a->OldY, -90, 1);
										entities.push_back(s);
									}
								}
								if (a->Species == 2)
								{
									if (a->R == 50)
									{
										Stern *s = new Stern();
										s->settings(sIconbullet, a->OldX, a->OldY, -90, 2);
										entities.push_back(s);
									}
								}
								a->life = false;
							}
						}
					}
					if (a->Species == 4)
						bloodboss = a->Blood;
				}

				if (a->name == "UFO" && b->name == "UFO")
				{
					if (isCollide(a, b, a->R, b->R))
					{
						b->OldY += 10;
						a->OldY -= 10;
					}
					if (Score > 5000)
						if (a->Species == 4)
							if (a->life == false)
								b->life = false;
				}

				if (a->name == "Ship" && b->name == "Stern")
				{
					if (isCollide(a, b, a->R, b->R))
					{
						//hồi máu
						if (b->Species == 0)
						{
							a->Blood += 2;
							hoimau = true;
							Frame_HoiMau = 10;
							if (a->Blood > 21)
								a->Blood = 21;
						}
						//thêm mạng
						if (b->Species == 1)
						{
							p->Health++;
							musicHealth.play();
							if (p->Health > 5)
								p->Health = 5;
						}
						//thêm đạn
						if (b->Species == 2)
						{
							AmountBullet++;
							musicIconBullet.play();
							musicIconBullet.setVolume(20);
							if (AmountBullet > 7)
								AmountBullet = 7;
						}
						b->life = false;
					}
				}

				//xử lý va chạm tàu bay của ta với UFO
				if (a->name == "Ship" && b->name == "UFO")
				{

					if (b->Species == 4)
					{
						if (isCollide(a, b, a->R, b->R3_UFO))
						{
							b->Angle = Angle(b->OldX, b->OldY, b->OldX + 10, b->OldY, a->OldX, a->OldY);
							b->YoungX = 0;
							b->YoungY = 0;
							if (isCollide(a, b, a->R, b->R))
							{
								musicShipDestroy.play();
								SetMusicEvent(musicShipDestroy, "images/Sound/SpaceDestroy.wav", 30);
								Entity *e = new Entity();
								e->settings(sExplosion_ship, a->OldX, a->OldY, 0, 0);
								e->name = "explosion";
								entities.push_back(e);

								p->settings(sPlayer, 800, 800, 20);
								p->Blood = 21;
								a->Health--;
								if (AmountBullet > 1)
									AmountBullet--;
								if (a->Health <= 0)
								{
									ShowScore = 1;
									p->R3_Ship = 0;
									p->R = 0;
									p->R2_Ship = 0;
									p->R1_Ship = 0;
									p->settings(sPlayer, 800, 800, 20);
								}
							}
							if (isCollide(a, b, a->R, b->R2_UFO))
							{
								b->frame_UFO += 0.05;
								if (b->frame_UFO >= b->time_UFO)
								{
									Rocket *r = new Rocket();
									r->settings(sBullet_UFO1, b->OldX - 90, b->OldY, b->Angle - 10, 0);
									entities.push_back(r);
									Rocket *e = new Rocket();
									e->settings(sBullet_UFO1, b->OldX + 100, b->OldY, b->Angle + 10, 0);
									entities.push_back(e);
									Rocket *k = new Rocket();
									k->settings(sBullet_UFO1, b->OldX, b->OldY, b->Angle + 10, 0);
									entities.push_back(k);
									Rocket *l = new Rocket();
									l->settings(sBullet_UFO1, b->OldX , b->OldY - 100, b->Angle + 10, 0);
									entities.push_back(l);
									Rocket *j = new Rocket();
									j->settings(sBullet_UFO1, b->OldX, b->OldY + 90, b->Angle + 10, 0);
									entities.push_back(j);


									b->frame_UFO = 2;
									musicYourRocket.play();
									musicYourRocket.setVolume(15);
								}
							}
						}
					}

					else if (b->Species == 5 || b->Species == 6)
					{
						if (isCollide(a, b, a->R, b->R3_UFO))
						{
							b->Angle = Angle(b->OldX, b->OldY, b->OldX + 10, b->OldY, a->OldX, a->OldY);
							b->YoungX = 0;
							b->YoungY = 0;
							if (isCollide(a, b, a->R, b->R2_UFO))
							{
								b->frame_UFO += 0.05;
								if (b->frame_UFO >= b->time_UFO)
								{
									if (b->Species == 5);
									{
										Bullet *g = new Bullet();
										g->settings(sBullet_UFO3, b->OldX, b->OldY, b->Angle + 7, 0);
										entities.push_back(g);
										Bullet * h = new Bullet();
										h->settings(sBullet_UFO3, b->OldX, b->OldY, b->Angle, 0);
										entities.push_back(h);
										Bullet *q = new Bullet();
										q->settings(sBullet_UFO3, b->OldX, b->OldY, b->Angle - 7, 0);
										entities.push_back(q);
										b->frame_UFO = 0;
										SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 15);
									}

									if (b->Species == 6)
									{
										Bullet *q = new Bullet();
										q->settings(sBullet_UFO2, b->OldX, b->OldY, b->Angle + 15, 2);
										entities.push_back(q);
										Bullet *g = new Bullet();
										g->settings(sBullet_UFO2, b->OldX, b->OldY, b->Angle, 2);
										entities.push_back(g);
										Bullet *h = new Bullet();
										h->settings(sBullet_UFO2, b->OldX, b->OldY, b->Angle - 15, 2);
										entities.push_back(h);
										b->frame_UFO = 0;
										SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 15);
									}
								}
							}
						}
					}

					else
					{
						if (isCollide(a, b, a->R, b->R))
						{
							b->life = false;
							p->Blood -= 5;
							Entity *e = new Entity();
							e->settings(sExplosion, b->OldX, b->OldY, 0, 0);
							e->name = "explosion";
							entities.push_back(e);
							musicUFODestroy.setVolume(30);
							musicUFODestroy.play();

							if (p->Blood <= 0)
							{
								//ship destroy
								musicShipDestroy.play();
								SetMusicEvent(musicShipDestroy, "images/Sound/SpaceDestroy.wav", 30);
								Entity *e = new Entity();
								e->settings(sExplosion_ship, a->OldX, a->OldY, 0, 0);
								e->name = "explosion";
								entities.push_back(e);

								p->settings(sPlayer, 800, 800, 20);
								p->Blood = 21;
								a->Health--;
								if (AmountBullet > 1)
									AmountBullet--;
								if (a->Health <= 0)
								{
									ShowScore = 1;
									//p->life = false;
									p->R3_Ship = 0;
									p->R = 0;
									p->R2_Ship = 0;
									p->R1_Ship = 0;
									p->Health = 0;
								}
							}
						}
						//nếu thằng b tìm được vị trí của thằng a thì thằng b sẽ bay về phía của thằng a
						if (isCollide(a, b, a->R, b->R3_UFO))
						{
							b->Angle = Angle(b->OldX, b->OldY, b->OldX + 10, b->OldY, a->OldX, a->OldY);
							b->YoungX = cos(b->Angle*DEGTORAD);
							b->YoungY = sin(b->Angle*DEGTORAD);
							//b->YoungX = AIinPutX(b->OldX, b->OldY, a->OldX, a->OldY);
							//b->YoungY = AIinPutY(b->OldX, b->OldY, a->OldX, a->OldY);
							//nếu thằng a nằm trong tầm ngắm của thằng b thì thằng b đứng lại và bắn thằng a
							if (isCollide(a, b, a->R, (b->R2_UFO + b->R)))
							{
								if (a->Species == 2 || b->Species == 3)
								{
									b->YoungX /= 4;
									b->YoungY /= 4;
								}
								else
								{
									b->YoungX = 0;
									b->YoungY = 0;
								}
								b->frame_UFO += 0.05;
								if (b->frame_UFO >= b->time_UFO)
								{
									if (b->Species == 3);
									{
										Bullet *q = new Bullet();
										q->settings(sBullet_UFO3, b->OldX, b->OldY, b->Angle, 0);
										entities.push_back(q);
										b->frame_UFO = 3;
										SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 15);
									}

									if (b->Species == 2)
									{
										Bullet *q = new Bullet();
										q->settings(sBullet_UFO2, b->OldX, b->OldY, b->Angle, 2);
										entities.push_back(q);
										b->frame_UFO = 3;
										SetMusicEvent(musicGun, "images/Sound/plasma_shot.wav", 15);
									}
									if (b->Species == 1)
									{
										Rocket *r = new Rocket();
										r->settings(sBullet_UFO1, b->OldX, b->OldY, b->Angle, 0);
										entities.push_back(r);
										b->frame_UFO = 1;
										musicYourRocket.play();
										musicYourRocket.setVolume(15);
									}
								}
							}
						}
					}
				}

				if (a->name == "Bullet" && b->name == "Rocket")
				{
					if (a->Species == 1 && b->Species == 0)
						if (isCollide(a, b, a->R, b->R))
						{
							a->life = false;
							b->Blood--;
							if (b->Blood <= 0)
								b->life = false;
							musicMyBullet_UFO.play();
						}
				}

				if (a->name == "Ship" && b->name == "Rocket")
				{
					//kiểm tra my ship có năm trong phạm vi của rocket dich hay ko?
					if (isCollide(b, a, b->R2_Rocket, a->R))
					{
						if (b->Species == 0)
							b->Angle = Angle(b->OldX, b->OldY, b->OldX + 10, b->OldY, a->OldX, a->OldY);
						if (isCollide(a, b, a->R, b->R))
						{
							if (b->Species == 0)
							{
								b->life = false;
								a->Blood -= 2;
								musicYourBullet_Ship.play();
								musicYourBullet_Ship.setVolume(30);
								if (a->Blood <= 0)
								{
									//ship destroy

									SetMusicEvent(musicShipDestroy, "images/Sound/SpaceDestroy.wav", 30);
									Entity *e = new Entity();
									e->settings(sExplosion_ship, a->OldX, a->OldY, 0, 0);
									e->name = "explosion";
									entities.push_back(e);
									p->settings(sPlayer, 800, 800, 20);
									p->Blood = 21;
									a->Health--;
									if (AmountBullet > 1)
										AmountBullet--;
									if (a->Health <= 0)
									{
										ShowScore = 1;
										p->R3_Ship = 0;
										p->R = 0;
										p->R2_Ship = 0;
										p->R1_Ship = 0;
										p->Health = 0;
									}
								}
							}
						}
					}
				}

				//nếu Rocket của ta tìm được và phá hủy được UFO của địch thì các UFO khác của địch trong bán kính 1000 đều bị phá hủy
				if (a->name == "UFO" && b->name == "Rocket")
				{
					if ((a->Species == 1 || a->Species == 0 || a->Species == 2 || a->Species == 3) && b->Species == 1)
					{
						if (isCollide(a, b, a->R2_UFO, b->R))
						{
							if (b->Species == 1)
								b->Angle = Angle(b->OldX, b->OldY, b->OldX + 10, b->OldY, a->OldX, a->OldY);
							if (isCollide(a, b, a->R, b->R))
							{
								if (b->Species == 1)
								{
									a->life = false;
									Entity *e = new Entity();
									e->settings(sExplosion, b->OldX, b->OldY, 0, 0);
									e->name = "explosion";
									entities.push_back(e);
									musicUFODestroy.setVolume(30);
									musicUFODestroy.play();
									for (auto c : entities)
									{
										if (b->name == "Rocket" && c->name == "UFO")
										{
											if (isCollide(b, c, b->R1_Rocket, c->R))
											{
												Score += 10;
												c->life = false;
												Entity *e = new Entity();
												e->settings(sExplosion, c->OldX, c->OldY, 0, 0);
												e->name = "explosion";
												entities.push_back(e);
												musicUFODestroy.setVolume(15);
												musicUFODestroy.play();
											}
										}
										if (c->name == "Rocket" && b->name == "Rocket")
										{
											if (c->Species == 0)
												if (isCollide(b, c, b->R1_Rocket, c->R))
													c->life = false;
										}
									}
									b->life = false;
								}
							}
						}
					}
				}

				if (a->name == "Ship" && b->name == "Bullet")
				{
					if (b->Species == 1)
					{
						if (!isCollide(a, b, a->R3_Ship, b->R))
						{
							b->life = false;
						}
					}
					if (b->Species != 1)
					{
						if (isCollide(a, b, a->R, b->R))
						{
							b->life = false;
							p->YoungX = 0;
							p->YoungY = 0;
							if (b->Species == 0)
							{
								check = false;
								Entity *e = new Entity();
								e->settings(sWebSpite, a->OldX, a->OldY, a->Angle, 0);
								e->name = "explosion";
								entities.push_back(e);
							}
							if (b->Species == 2)
							{
								p->Angle += 90;
							}
							musicYourBullet_Ship.play();
							musicYourBullet_Ship.setVolume(15);
							a->Blood--;
							if (a->Blood <= 0)
							{
								//ship destroy
								SetMusicEvent(musicShipDestroy, "images/Sound/SpaceDestroy.wav", 30);
								Entity *E = new Entity();
								E->settings(sExplosion_ship, a->OldX, a->OldY, 0, 0);
								E->name = "explosion";
								entities.push_back(E);

								p->settings(sPlayer, 800, 800, 20);
								p->Blood = 21;
								a->Health--;
								if (AmountBullet > 1)
									AmountBullet--;

								if (a->Health <= 0)
								{
									ShowScore = 1;
									p->R3_Ship = 0;
									p->R = 0;
									p->R2_Ship = 0;
									p->R1_Ship = 0;
									p->Health = 0;
								}
							}
						}
					}
				}
			}

		if (p->thrust)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;

		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

		if (Frame_kill > Time_wait)
		{
			int goc;
			for (int j = 0; j < 30; j++)
			{
				Asteroid *a = new Asteroid();
				goc = rand() % 360;
				if (goc < 180)
					a->settings(sRock, rand() % 6000, 5, goc, 25);
				else
					a->settings(sRock, rand() % 6000, 3995, goc, 25);
				entities.push_back(a);
			}

			for (int i = 0; i < (7 - kill); i++)
			{
				if (Score > 20)
				{
					kill = 1;
					UFO *a = new UFO();
					a->settings(sUFO3, rand() % 1000 + 5000, rand() % 500, (rand() % 5 + 2) * 10, 500, 30, 3, 4);
					entities.push_back(a);
				}

				if (Score > 800)
				{
					kill = 2;
					UFO *a = new UFO();
					a->settings(sUFO2, rand() % 1000 + 5500, rand() % 2000, (rand() % 5 + 2) * 10, 700, 30, 2, 3);
					entities.push_back(a);

					UFO *b = new UFO();
					b->settings(sUFO3, rand() % 1000 + 5500, rand() % 2000, (rand() % 5 + 2) * 10, 500, 30, 3, 3);
					entities.push_back(b);

				}

				if (Score > 5000)
				{
					kill = 3;
					UFO *a = new UFO();
					a->settings(sUFO3, rand() % 1000 + 6000, rand() % 500 + 0, (rand() % 5 + 2) * 10, 500, 30, 3, 3);
					entities.push_back(a);

					UFO *b = new UFO();
					b->settings(sUFO2, rand() % 1000 + 5000, rand() % 500, (rand() % 5 + 2) * 10, 700, 30, 2, 3);
					entities.push_back(b);

					UFO *c = new UFO();
					c->settings(sUFO1, rand() % 500, rand() % 3000 + 0, (rand() % 5 + 2) * 10, 1500, rand() % 360, 1, 3);
					entities.push_back(c);
					
				}
				cout << kill << endl;
			}
			Frame_kill = kill * 2 + 3;
		}


		

		if (ShowScore == 1 || ShowScore == 2)
		{
			for (auto a : entities)
				if (a->name == "UFO")
				{
					a->life = false;
				}
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}



			//////draw//////

			//location Time Khiên (p->oldX - 282, p->oldY - 431)
			//location Time Rocket (p->oldX + 210, p->oldY - 431)

			//iconTime_k.setPosition(view.getCenter().x - 282, view.getCenter().y + 431);
			//iconTime_r.setPosition(view.getCenter().x + 320, view.getCenter().y + 431);

			Blood.setTextureRect(IntRect(40 * p->Blood, 0, 40, 400));
			Blood.setPosition(view.getCenter().x - 909, view.getCenter().y - 249);

			BloodBoss.setTextureRect(IntRect(0, 40 * bloodboss, 400, 40));
			BloodBoss.setPosition(view.getCenter().x - 750, view.getCenter().y - 510);

			app.clear();
			app.draw(background);
			if (Score > 2000)
				app.draw(sBoss);

			for (auto i : entities)
				i->draw(app);

			app.draw(UI);
			app.draw(Blood);
			app.draw(BloodBoss);
			/*if (Frame_Tank < Time_wait)
			{
				app.draw(iconTime_k);
			}
			if (Frame_Rocket < Time_wait)
			{
				app.draw(iconTime_r);
			}*/
			app.draw(text);
			app.draw(health);
			app.draw(textminute);
			app.draw(textSecond);

			if (ShowScore == 1)
			{
				app.draw(sscore);
				app.draw(Deaf);
				text.setPosition(UI.getPosition().x + 920, UI.getPosition().y + 600);
				app.draw(text);//show điểm
				ShowMenu = true;//show menu
				check = false;//không cho ship di chuyển
				//app.setMouseCursorVisible(true);
			}
			else if (ShowScore == 2)
			{
				app.draw(sscore);
				app.draw(Win);
				text.setPosition(UI.getPosition().x + 920, UI.getPosition().y + 600);
				app.draw(text);//show điểm
				ShowMenu = true;//show menu
				check = false;//không cho ship di chuyển
			}
			app.draw(IconMouse);
			app.display();
		}

		return 0;
	}