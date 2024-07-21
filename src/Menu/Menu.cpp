#include "Menu.h"
#include <iostream>

Menu::~Menu()
{
	for (auto scene = m_scenes.begin(); scene != m_scenes.end(); scene++)
	{
		//scene->second.freeMemory();
	}
	logger->log(LogLevel::INFO, "Scene Memory Freed", "~Menu", "Menu");
}

void Menu::setupDialogueRenderer(SharedString* dialogueText)
{
	Overlay dialogue(m_renderer);

	TextBox* topLine = new TextBox;
	TextBox* botLine = new TextBox;

	topLine->dynamic_text = &dialogueText->string1;
	botLine->dynamic_text = &dialogueText->string2;

	topLine->renderData = TextBoxRenderData{ 3.0f, 12.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	botLine->renderData = TextBoxRenderData{ 3.0f, 4.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

	dialogue.addTextBox(topLine);
	dialogue.addTextBox(botLine);

	m_overlays[MenuOverlay::DIALOGUE] = dialogue;
}

void Menu::setupKeyboard(AlphabetStringData* alphabet, std::string* input)
{
	Overlay onScreenKeyboard(m_renderer);	//Keyboard should be its own class too

	TextBox* keyboardInput = new TextBox;

	keyboardInput->dynamic_text = input;

	Button* a = new Button;
	Button* b = new Button;
	Button* c = new Button;
	Button* d = new Button;
	Button* e = new Button;
	Button* f = new Button;
	Button* g = new Button;
	Button* h = new Button;
	Button* i = new Button;
	Button* j = new Button;
	Button* k = new Button;
	Button* l = new Button;
	Button* m = new Button;
	Button* n = new Button;
	Button* o = new Button;
	Button* p = new Button;
	Button* q = new Button;
	Button* r = new Button;
	Button* s = new Button;
	Button* t = new Button;
	Button* u = new Button;
	Button* v = new Button;
	Button* w = new Button;
	Button* x = new Button;
	Button* y = new Button;
	Button* z = new Button;

	Button* colon = new Button;
	Button* apostrophe = new Button;

	Button* one = new Button;
	Button* two = new Button;
	Button* three = new Button;
	Button* four = new Button;
	Button* five = new Button;
	Button* six = new Button;
	Button* seven = new Button;
	Button* eight = new Button;
	Button* nine = new Button;
	Button* zero = new Button;

	Button* shift = new Button;
	Button* space = new Button;
	Button* del = new Button;
	Button* enter = new Button;
	
	// Text
	{
		a->dynamic_text = &alphabet->a_f.string1;
		b->dynamic_text = &alphabet->a_f.string2;
		c->dynamic_text = &alphabet->a_f.string3;
		d->dynamic_text = &alphabet->a_f.string4;
		e->dynamic_text = &alphabet->a_f.string5;
		f->dynamic_text = &alphabet->a_f.string6;
		g->dynamic_text = &alphabet->g_l.string1;
		h->dynamic_text = &alphabet->g_l.string2;
		i->dynamic_text = &alphabet->g_l.string3;
		j->dynamic_text = &alphabet->g_l.string4;
		k->dynamic_text = &alphabet->g_l.string5;
		l->dynamic_text = &alphabet->g_l.string6;
		m->dynamic_text = &alphabet->m_r.string1;
		n->dynamic_text = &alphabet->m_r.string2;
		o->dynamic_text = &alphabet->m_r.string3;
		p->dynamic_text = &alphabet->m_r.string4;
		q->dynamic_text = &alphabet->m_r.string5;
		r->dynamic_text = &alphabet->m_r.string6;
		s->dynamic_text = &alphabet->s_x.string1;
		t->dynamic_text = &alphabet->s_x.string2;
		u->dynamic_text = &alphabet->s_x.string3;
		v->dynamic_text = &alphabet->s_x.string4;
		w->dynamic_text = &alphabet->s_x.string5;
		x->dynamic_text = &alphabet->s_x.string6;
		y->dynamic_text = &alphabet->y_z.string1;
		z->dynamic_text = &alphabet->y_z.string2;

		one->text = "1";
		two->text = "2";
		three->text = "3";
		four->text = "4";
		five->text = "5";
		six->text = "6";
		seven->text = "7";
		eight->text = "8";
		nine->text = "9";
		zero->text = "0";

		colon->text = ":";
		apostrophe->text = "\'";

		del->text = "Del";
		enter->text = "Enter";
	}

	// Data
	{
		a->data = 1;
		b->data = 2;
		c->data = 3;
		d->data = 4;
		e->data = 5;
		f->data = 6;
		g->data = 7;
		h->data = 8;
		i->data = 9;
		j->data = 10;
		k->data = 11;
		l->data = 12;
		m->data = 13;
		n->data = 14;
		o->data = 15;
		p->data = 16;
		q->data = 17;
		r->data = 18;
		s->data = 19;
		t->data = 20;
		u->data = 21;
		v->data = 22;
		w->data = 23;
		x->data = 24;
		y->data = 25;
		z->data = 26;

		colon->data = 27;
		apostrophe->data = 28;

		one->data = 29;
		two->data = 30;
		three->data = 31;
		four->data = 32;
		five->data = 33;
		six->data = 34;
		seven->data = 35;
		eight->data = 36;
		nine->data = 37;
		zero->data = 38;

		shift->data = 39;
		space->data = 40;
		del->data = 41;
		enter->data = 42;
	}

	// Link Elements
	{
		// Number Row
		{
			one->down = q;
			one->right = two;
			two->down = w;
			two->left = one;
			two->right = three;
			three->left = two;
			three->down = e;
			three->right = four;
			four->left = three;
			four->down = r;
			four->right = five;
			five->left = four;
			five->down = t;
			five->right = six;
			six->left = five;
			six->down = y;
			six->right = seven;
			seven->left = six;
			seven->down = u;
			seven->right = eight;
			eight->left = seven;
			eight->down = i;
			eight->right = nine;
			nine->left = eight;
			nine->down = o;
			nine->right = zero;
			zero->left = nine;
			zero->down = p;
		}
		
		// Colon Row
		{
			colon->up = one;
			colon->down = shift;
			colon->right = q;

			q->up = one;
			q->down = a;
			q->left = colon;
			q->right = w;

			w->up = two;
			w->down = s;
			w->left = q;
			w->right = e;

			e->up = three;
			e->down = d;
			e->left = w;
			e->right = r;

			r->up = four;
			r->down = f;
			r->left = e;
			r->right = t;

			t->up = five;
			t->down = g;
			t->left = r;
			t->right = y;

			y->up = six;
			y->down = h;
			y->left = t;
			y->right = u;

			u->up = seven;
			u->down = j;
			u->left = y;
			u->right = i;

			i->up = eight;
			i->down = k;
			i->left = u;
			i->right = o;

			o->up = nine;
			o->down = l;
			o->left = i;
			o->right = p;

			p->up = zero;
			p->down = del;
			p->left = o;
			p->right = apostrophe;

			apostrophe->up = zero;
			apostrophe->down = del;
			apostrophe->left = p;
		}

		// A Row
		{
			shift->up = colon;
			shift->down = space;
			shift->right = a;

a->up = q;
a->down = z;
a->left = shift;
a->right = s;

s->up = w;
s->down = z;
s->left = a;
s->right = d;

d->up = e;
d->down = x;
d->left = s;
d->right = f;

f->up = r;
f->down = c;
f->left = d;
f->right = g;

g->up = t;
g->down = v;
g->left = f;
g->right = h;

h->up = y;
h->down = b;
h->left = g;
h->right = j;

j->up = u;
j->down = n;
j->left = h;
j->right = k;

k->up = i;
k->down = m;
k->left = j;
k->right = l;

l->up = o;
l->down = m;
l->left = k;
l->right = del;

del->up = p;
del->down = enter;
del->left = l;
		}

		// Z Row
		{
		z->up = s;
		z->down = space;
		z->left = shift;
		z->right = x;

		x->up = d;
		x->down = space;
		x->left = z;
		x->right = c;

		c->up = f;
		c->down = space;
		c->left = x;
		c->right = v;

		v->up = g;
		v->down = space;
		v->left = c;
		v->right = b;

		b->up = h;
		b->down = space;
		b->left = v;
		b->right = n;

		n->up = j;
		n->down = space;
		n->left = b;
		n->right = m;

		m->up = k;
		m->down = space;
		m->left = n;
		m->right = enter;

		enter->up = del;
		enter->left = m;
		enter->down = space;

		space->up = v;
		space->left = shift;
		space->right = enter;
		}

	}

	{}	// The render data tab in visual studio wont collapse without it lol

	// Render Data
	{
		float spacing = 1.82f;
		float buttonSize = 5.0f;

		float bottomPadding = 10.0f;
		float leftPadding = (100 - ((12 * buttonSize) + (11 * spacing))) / 2.0f;
		float spaceBarMultiplier = 9.0f;

		Color buttonColor = Color::RED;

		space->renderData = ButtonRenderData{ 50.0f, bottomPadding + (buttonSize / 2.0f), buttonSize * spaceBarMultiplier, buttonSize, buttonColor };
		shift->renderData = ButtonRenderData{ leftPadding + buttonSize / 2.0f , space->renderData.percentageY + (buttonSize / 2.0f) + spacing + buttonSize + (spacing / 2.0f), buttonSize, (buttonSize * 2) + spacing, buttonColor};
		colon->renderData = ButtonRenderData{ shift->renderData.percentageX, shift->renderData.percentageY + (shift->renderData.heightPercent / 2.0f) + spacing + (buttonSize / 2.0f), buttonSize, buttonSize, buttonColor };
		q->renderData = ButtonRenderData{ colon->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY, buttonSize, buttonSize, buttonColor };
		w->renderData = ButtonRenderData{ q->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		e->renderData = ButtonRenderData{ w->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		r->renderData = ButtonRenderData{ e->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		t->renderData = ButtonRenderData{ r->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		y->renderData = ButtonRenderData{ t->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		u->renderData = ButtonRenderData{ y->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		i->renderData = ButtonRenderData{ u->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		o->renderData = ButtonRenderData{ i->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		p->renderData = ButtonRenderData{ o->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		apostrophe->renderData = ButtonRenderData{ p->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		a->renderData = ButtonRenderData{ q->renderData.percentageX, q->renderData.percentageY - buttonSize - spacing, buttonSize, buttonSize, buttonColor };
		s->renderData = ButtonRenderData{ a->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY, buttonSize, buttonSize, buttonColor };
		d->renderData = ButtonRenderData{ s->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		f->renderData = ButtonRenderData{ d->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		g->renderData = ButtonRenderData{ f->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		h->renderData = ButtonRenderData{ g->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		j->renderData = ButtonRenderData{ h->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		k->renderData = ButtonRenderData{ j->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		l->renderData = ButtonRenderData{ k->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		del->renderData = ButtonRenderData{ l->renderData.percentageX + (buttonSize / 2.0f) + spacing + buttonSize + (spacing / 2.0f), a->renderData.percentageY, (buttonSize * 2) + spacing, buttonSize, buttonColor};
		z->renderData = ButtonRenderData{ s->renderData.percentageX, s->renderData.percentageY - buttonSize - spacing, buttonSize, buttonSize, buttonColor };
		x->renderData = ButtonRenderData{ z->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		c->renderData = ButtonRenderData{ x->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		v->renderData = ButtonRenderData{ c->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		b->renderData = ButtonRenderData{ v->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		n->renderData = ButtonRenderData{ b->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		m->renderData = ButtonRenderData{ n->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };

		enter->renderData = ButtonRenderData{ del->renderData.percentageX, del->renderData.percentageY - buttonSize - spacing, buttonSize * 2, buttonSize, buttonColor };

		one->renderData = ButtonRenderData{ q->renderData.percentageX, q->renderData.percentageY + buttonSize + spacing,buttonSize, buttonSize, buttonColor };
		two->renderData = ButtonRenderData{ one->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		three->renderData = ButtonRenderData{ two->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		four->renderData = ButtonRenderData{ three->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		five->renderData = ButtonRenderData{ four->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		six->renderData = ButtonRenderData{ five->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		seven->renderData = ButtonRenderData{ six->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		eight->renderData = ButtonRenderData{ seven->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		nine->renderData = ButtonRenderData{ eight->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		zero->renderData = ButtonRenderData{ nine->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
	
		keyboardInput->renderData = TextBoxRenderData{ leftPadding - buttonSize, 65.0f, 10.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	}

	// Add Elements
	{
		onScreenKeyboard.addButton(a);
		onScreenKeyboard.addButton(b);
		onScreenKeyboard.addButton(c);
		onScreenKeyboard.addButton(d);
		onScreenKeyboard.addButton(e);
		onScreenKeyboard.addButton(f);
		onScreenKeyboard.addButton(g);
		onScreenKeyboard.addButton(h);
		onScreenKeyboard.addButton(i);
		onScreenKeyboard.addButton(j);
		onScreenKeyboard.addButton(k);
		onScreenKeyboard.addButton(l);
		onScreenKeyboard.addButton(m);
		onScreenKeyboard.addButton(n);
		onScreenKeyboard.addButton(o);
		onScreenKeyboard.addButton(p);
		onScreenKeyboard.addButton(q);
		onScreenKeyboard.addButton(r);
		onScreenKeyboard.addButton(s);
		onScreenKeyboard.addButton(t);
		onScreenKeyboard.addButton(u);
		onScreenKeyboard.addButton(v);
		onScreenKeyboard.addButton(w);
		onScreenKeyboard.addButton(x);
		onScreenKeyboard.addButton(y);
		onScreenKeyboard.addButton(z);
		onScreenKeyboard.addButton(colon);
		onScreenKeyboard.addButton(apostrophe);
		onScreenKeyboard.addButton(one);
		onScreenKeyboard.addButton(two);
		onScreenKeyboard.addButton(three);
		onScreenKeyboard.addButton(four);
		onScreenKeyboard.addButton(five);
		onScreenKeyboard.addButton(six);
		onScreenKeyboard.addButton(seven);
		onScreenKeyboard.addButton(eight);
		onScreenKeyboard.addButton(nine);
		onScreenKeyboard.addButton(zero);
		onScreenKeyboard.addButton(shift);
		onScreenKeyboard.addButton(space);
		onScreenKeyboard.addButton(del);
		onScreenKeyboard.addButton(enter);
	}

	onScreenKeyboard.addTextBox(keyboardInput);
	m_overlays[MenuOverlay::ON_SCREEN_KEYBOARD] = onScreenKeyboard;
}

void Menu::setupIntroData(bool* studioVisible, bool* pressAnyButtonVisible)
{
	{
		Scene introLinksScene(m_renderer);
		introLinksScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LINKS]);
		m_scenes[MenuScene::INTRO_LINKS] = introLinksScene;
	}

	{
		Scene introStudio(m_renderer);
		introStudio.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_STUDIO]);
		m_scenes[MenuScene::INTRO_STUDIO] = introStudio;
	}

	{
		Scene introStudioCrown(m_renderer);
		introStudioCrown.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_STUDIO_CROWN]);
		m_scenes[MenuScene::INTRO_STUDIO_CROWN] = introStudioCrown;
	}

	{
		Scene introLegendaryPokemon(m_renderer);
		introLegendaryPokemon.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LEGENDARY]);
		m_scenes[MenuScene::INTRO_LEGENDARY] = introLegendaryPokemon;
	}

	{
		Scene introPressAnyButton(m_renderer);

		//introLegendaryScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LEGENDARY]);

		TextBox* pressAnyButton = new TextBox;
		TextBox* pressAnyButtonOutline = new TextBox;
		TextBox* pokemonGameVersion = new TextBox;
		TextBox* pokemonGameVersionOutline = new TextBox;

		pressAnyButtonOutline->text = "PRESS ANY BUTTON";
		pressAnyButton->text = "PRESS ANY BUTTON";
		pokemonGameVersionOutline->text = "POKEMON PRIDE VERSION";
		pokemonGameVersion->text = "POKEMON PRIDE VERSION";

		pressAnyButtonOutline->visible = pressAnyButtonVisible;
		pressAnyButton->visible = pressAnyButtonVisible;

		float xPos = 50.0f;
		float yPos = 1.5f;

		float xDrop = 0.3f;
		float yDrop = 0.3f;

		float ySpacing = 12.0f;
		
		pokemonGameVersionOutline->renderData = TextBoxRenderData{ xPos - xDrop, yPos + ySpacing - yDrop, 3.0f, Color::BLACK };
		pokemonGameVersion->renderData = TextBoxRenderData{ xPos - xDrop, yPos + ySpacing - yDrop, 3.0f, Color::WHITE };
		pressAnyButtonOutline->renderData = TextBoxRenderData{ xPos - xDrop, yPos - yDrop, 3.0f, Color::BLACK};
		pressAnyButton->renderData = TextBoxRenderData{ xPos, yPos, 3.0f, Color::WHITE};


		introPressAnyButton.addTextBox(pokemonGameVersionOutline);
		introPressAnyButton.addTextBox(pokemonGameVersion);
		introPressAnyButton.addTextBox(pressAnyButtonOutline);
		introPressAnyButton.addTextBox(pressAnyButton);

		m_scenes[MenuScene::INTRO_PRESS_ANY_BUTTON] = introPressAnyButton;
	}

	{
		Scene playerNameScene(m_renderer);
		playerNameScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::SET_PLAYER_NAME]);

		TextBox* playerNameText = new TextBox;
		playerNameText->text = "NAME:";
		playerNameText->renderData = TextBoxRenderData{ 50.0f, 83.0f, 10.0f };
		playerNameScene.addTextBox(playerNameText);

		m_scenes[MenuScene::SET_PLAYER_NAME] = playerNameScene;
	}

	{
		Scene professorMScene(m_renderer);
		professorMScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::PROFESSOR_M]);
		m_scenes[MenuScene::PROFESSOR_M] = professorMScene;
	}
	
}

void Menu::setupStartupData(SharedString* header1, SharedString* header2, SharedString* header3, bool* f1Visible, bool* f2Visible, bool* f3Visible)
{
	//Startup Scene
	{
		Scene startupScene(m_renderer);
		startupScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::STARTUP_SCENE]);

		Button* playFile1 = new Button;
		Button* playFile2 = new Button;
		Button* playFile3 = new Button;

		Button* deleteFile1 = new Button;
		Button* deleteFile2 = new Button;
		Button* deleteFile3 = new Button;

		TextBox* file1PlayerName = new TextBox;
		TextBox* file2PlayerName = new TextBox;
		TextBox* file3PlayerName = new TextBox;

		TextBox* file1PlayTime = new TextBox;
		TextBox* file2PlayTime = new TextBox;
		TextBox* file3PlayTime = new TextBox;

		TextBox* file1PokedexFound = new TextBox;
		TextBox* file2PokedexFound = new TextBox;
		TextBox* file3PokedexFound = new TextBox;

		TextBox* file1Badges = new TextBox;
		TextBox* file2Badges = new TextBox;
		TextBox* file3Badges = new TextBox;


		playFile1->data = 0;
		playFile2->data = 1;
		playFile3->data = 2;

		deleteFile1->data = 3;
		deleteFile2->data = 4;
		deleteFile3->data = 5;

		deleteFile1->overlay = MenuOverlay::DELETE_CONFIRMATION;
		deleteFile2->overlay = MenuOverlay::DELETE_CONFIRMATION;
		deleteFile3->overlay = MenuOverlay::DELETE_CONFIRMATION;

		playFile1->text = "PlAY";
		playFile2->text = "PlAY";
		playFile3->text = "PlAY";
		deleteFile1->text = "DElETE";
		deleteFile2->text = "DElETE";
		deleteFile3->text = "DElETE";
		
		
		playFile1->down = deleteFile1;
		playFile1->right = playFile2;
		
		playFile2->left = playFile1;
		playFile2->right = playFile3;
		playFile2->down = deleteFile2;
		
		playFile3->left = playFile2;
		playFile3->down = deleteFile3;
		
		deleteFile1->up = playFile1;
		deleteFile1->right = deleteFile2;
		
		deleteFile2->up = playFile2;
		deleteFile2->left = deleteFile1;
		deleteFile2->right = deleteFile3;
		
		deleteFile3->up = playFile3;
		deleteFile3->left = deleteFile2;
		
		deleteFile1->visible = f1Visible;
		deleteFile2->visible = f2Visible;
		deleteFile3->visible = f3Visible;
		
		file1PlayerName->dynamic_text = &header1->string1;
		file2PlayerName->dynamic_text = &header2->string1;
		file3PlayerName->dynamic_text = &header3->string1;
		
		file1PlayTime->dynamic_text = &header1->string2;
		file2PlayTime->dynamic_text = &header2->string2;
		file3PlayTime->dynamic_text = &header3->string2;
		
		file1PokedexFound->dynamic_text = &header1->string3;
		file2PokedexFound->dynamic_text = &header2->string3;
		file3PokedexFound->dynamic_text = &header3->string3;
		
		file1Badges->dynamic_text = &header1->string4;
		file2Badges->dynamic_text = &header2->string4;
		file3Badges->dynamic_text = &header3->string4;
		
		
		playFile1->renderData = ButtonRenderData{ 20.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };
		playFile2->renderData = ButtonRenderData{ 50.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };
		playFile3->renderData = ButtonRenderData{ 80.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };
		
		deleteFile1->renderData = ButtonRenderData{ 20.0f, 40.0f, 5.0f, 2.5f, Color::RED };
		deleteFile2->renderData = ButtonRenderData{ 50.0f, 40.0f, 5.0f, 2.5f, Color::RED };
		deleteFile3->renderData = ButtonRenderData{ 80.0f, 40.0f, 5.0f, 2.5f, Color::RED };
		
		
		file1PlayerName->renderData = TextBoxRenderData{ 20.0f, 70.0f, 2.0f };
		file2PlayerName->renderData = TextBoxRenderData{ 50.0f, 70.0f, 2.0f };
		file3PlayerName->renderData = TextBoxRenderData{ 80.0f, 70.0f, 2.0f };
		
		file1PlayTime->renderData = TextBoxRenderData{ 20.0f, 65.0f, 2.0f };
		file2PlayTime->renderData = TextBoxRenderData{ 50.0f, 65.0f, 2.0f };
		file3PlayTime->renderData = TextBoxRenderData{ 80.0f, 65.0f, 2.0f };
		
		file1PokedexFound->renderData = TextBoxRenderData{ 20.0f, 60.0f, 2.0f };
		file2PokedexFound->renderData = TextBoxRenderData{ 50.0f, 60.0f, 2.0f };
		file3PokedexFound->renderData = TextBoxRenderData{ 80.0f, 60.0f, 2.0f };
		
		file1Badges->renderData = TextBoxRenderData{ 20.0f, 55.0f, 2.0f };
		file2Badges->renderData = TextBoxRenderData{ 50.0f, 55.0f, 2.0f };
		file3Badges->renderData = TextBoxRenderData{ 80.0f, 55.0f, 2.0f };
		
		
		
		startupScene.addButton(playFile2);
		startupScene.addButton(playFile1);
		startupScene.addButton(playFile3);
		startupScene.addButton(deleteFile1);
		startupScene.addButton(deleteFile2);
		startupScene.addButton(deleteFile3);
		
		
		startupScene.addTextBox(file1PlayerName);
		startupScene.addTextBox(file2PlayerName);
		startupScene.addTextBox(file3PlayerName);
		
		startupScene.addTextBox(file1PlayTime);
		startupScene.addTextBox(file2PlayTime);
		startupScene.addTextBox(file3PlayTime);
		
		startupScene.addTextBox(file1PokedexFound);
		startupScene.addTextBox(file2PokedexFound);
		startupScene.addTextBox(file3PokedexFound);
		
		startupScene.addTextBox(file1Badges);
		startupScene.addTextBox(file2Badges);
		startupScene.addTextBox(file3Badges);
		
		m_scenes[MenuScene::STARTUP_SCENE] = startupScene;
	}


	// Delete Confirmation
	{
		Overlay deleteConfirmation(m_renderer);
		deleteConfirmation.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 30.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });


		TextBox* confirmMessage = new TextBox;
		Button* yes = new Button;
		Button* no = new Button;

		confirmMessage->text = "Delete Save";
		yes->text = "YES";
		no->text = "NO";

		yes->right = no;
		no->left = yes;


		yes->data = 0;
		no->data = 1;


		confirmMessage->renderData = TextBoxRenderData{50.0f, 55.0f, 5.0f};
		yes->renderData = ButtonRenderData{ 45.0f, 45.0f, 10.0f, 7.5f };
		no->renderData = ButtonRenderData{ 55.0f, 45.0f, 10.0f, 7.5f };

		deleteConfirmation.addButton(no);
		deleteConfirmation.addButton(yes);
		deleteConfirmation.addTextBox(confirmMessage);

		m_overlays[MenuOverlay::DELETE_CONFIRMATION] = deleteConfirmation;
	}
	
	
}

void Menu::setupBattleData(SharedString* moves, SimulationCommand* menuCommand, RosterDisplayData* rosterData, ItemDisplayData* battleItemData, BattlePokemonData* battleData, DynamicImageRenderData* playerPokemon, DynamicImageRenderData* oppPokemon)
{
	m_menuCommand = menuCommand;

	//		Main Battle
	{
		Scene mainBattle(m_renderer);
		mainBattle.setBackgroundPath(g_sceneTextureLocations[MenuScene::BATTLE]);

		mainBattle.addDynamicImage(playerPokemon);
		mainBattle.addDynamicImage(oppPokemon);

		TextBox* playerName = new TextBox;
		TextBox* opponentName = new TextBox;

		TextBox* playerLevel = new TextBox;
		TextBox* opponentLevel = new TextBox;

		TextBox* currentHP = new TextBox;
		TextBox* maxHP = new TextBox;

		playerName->dynamic_text = &battleData->playerName;
		opponentName->dynamic_text = &battleData->opponentName;

		playerLevel->dynamic_text = &battleData->playerLevel;
		opponentLevel->dynamic_text = &battleData->opponentLevel;

		currentHP->dynamic_text = &battleData->currentHP;
		maxHP->dynamic_text = &battleData->maxHP;


		playerName->renderData = TextBoxRenderData{ 52.0f, 45.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		opponentName->renderData = TextBoxRenderData{ 0.0f, 77.5f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		playerLevel->renderData = TextBoxRenderData{ 98.0f, 45.0f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		opponentLevel->renderData = TextBoxRenderData{ 38.0f, 77.5f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

		currentHP->renderData = TextBoxRenderData{ 85.0f, 30.0f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		maxHP->renderData = TextBoxRenderData{ 85.0f, 30.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		mainBattle.addTextBox(playerName);
		mainBattle.addTextBox(opponentName);
		mainBattle.addTextBox(playerLevel);
		mainBattle.addTextBox(opponentLevel);
		mainBattle.addTextBox(currentHP);
		mainBattle.addTextBox(maxHP);
		

		float yMultiplier = (1080.0f / 563.0f);
		float xMultiplier = (1920.0f / 1000.0f);

		//TODO: Use normal measuements
		mainBattle.addRectangle(new RectangleRenderData{(745.0f/1920.0f) * 100 * xMultiplier, (221.0f /1080.0f) * 100 * yMultiplier, (27.0f / 1080.0f) * 100 * yMultiplier, &battleData->playerCurHPPercent});
		mainBattle.addRectangle(new RectangleRenderData{(187.0f/1920.0f) * 100 * xMultiplier, (414.0f /1080.0f) * 100 * yMultiplier, (24.0f/1080.0f) * 100 * yMultiplier, &battleData->opponentCurHPPercent});
		mainBattle.addRectangle(new RectangleRenderData{(587.0f/1920.0f) * 100 * xMultiplier, (159.0f /1080.0f) * 100 * yMultiplier, (14.0f/1080.0f) * 100 * yMultiplier, &battleData->playerXPPercent, Color::BLUE});

		m_scenes[MenuScene::BATTLE] = mainBattle;
	}


	//		Main Battle Options
	{
		Overlay mainBattleOptions(m_renderer);
		mainBattleOptions.setText("What would you like to do\n1) Fight  2) Pokemon\n3) Items  4) Flee\n");

		Button* fightButton = new Button;
		Button* pokemonButton = new Button;
		Button* itemButton = new Button;
		Button* fleeButton = new Button;

		TextBox* topLine = new TextBox;
		TextBox* bottomLine = new TextBox;

		fightButton->data = SimulationType::ATTACK_SELECTED;
		pokemonButton->data = SimulationType::POKEMON_SELECTED;
		itemButton->data = SimulationType::ITEM_SELECTED;
		fleeButton->data = SimulationType::FLEE_SELECTED;


		fightButton->text = "FIGHT";
		pokemonButton->text = "POKEMON";
		itemButton->text = "ITEM";
		fleeButton->text = "FLEE";

		topLine->text = "What should";
		bottomLine->dynamic_text = &battleData->botLine;

		fightButton->right = itemButton;
		fightButton->down = pokemonButton;
		fightButton->overlay = MenuOverlay::ATTACK_SELECT;

		pokemonButton->up = fightButton;
		pokemonButton->right = fleeButton;
		pokemonButton->scene = MenuScene::BATTLE_ROSTER;

		itemButton->left = fightButton;
		itemButton->down = fleeButton;
		itemButton->scene = MenuScene::BATTLE_ITEMS;

		fleeButton->up = itemButton;
		fleeButton->left = pokemonButton;

		fightButton->renderData =	ButtonRenderData{ 63.5f,	17.75f, 19.0f, 6.5f, Color::RED };
		pokemonButton->renderData = ButtonRenderData{ 63.5f,	7.25f,	19.0f, 6.5f, Color::RED };
		itemButton->renderData =	ButtonRenderData{ 86.5f,	17.75f, 19.0f, 6.5f, Color::RED };	//TODO: Find Better button colors
		fleeButton->renderData =	ButtonRenderData{ 86.5f,	7.25f,	19.0f, 6.5f, Color::RED };	//TODO: Find Better button colors

		topLine->renderData = TextBoxRenderData{ 3.0f, 12.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		bottomLine->renderData = TextBoxRenderData{ 3.0f, 4.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		mainBattleOptions.addButton(fightButton);
		mainBattleOptions.addButton(pokemonButton);
		mainBattleOptions.addButton(itemButton);
		mainBattleOptions.addButton(fleeButton);

		mainBattleOptions.setOverlayBackground(new ImageRenderData{25.5f, 12.5f, 24.0f, 10.0f, g_overlayTextureLocations[MenuOverlay::BATTLE_CHAT]});

		mainBattleOptions.addTextBox(topLine);
		mainBattleOptions.addTextBox(bottomLine);

		m_overlays[MenuOverlay::BATTLE_OPTIONS] = mainBattleOptions;
	}

	//		Fight Screen
	{
		Overlay fightScreen(m_renderer);
		fightScreen.setText("");

		Button* move1 = new Button;
		Button* move2 = new Button;
		Button* move3 = new Button;
		Button* move4 = new Button;

		move1->data = 0;
		move2->data = 1;
		move3->data = 2;
		move4->data = 3;

		move1->dynamic_text = &moves->string1;
		move2->dynamic_text = &moves->string2;
		move3->dynamic_text = &moves->string3;
		move4->dynamic_text = &moves->string4;

		move1->right = move2;
		move1->down = move3;

		move2->left = move1;
		move2->down = move4;

		move3->up = move1;
		move3->right = move4;

		move4->up = move2;
		move4->left = move3;

		move1->renderData = ButtonRenderData{ 25.0f, 18.0f, 40.0f, 8.0f, Color::RED };
		move2->renderData = ButtonRenderData{ 75.0f, 18.0f, 40.0f, 8.0f, Color::RED };
		move3->renderData = ButtonRenderData{ 25.0f,  7.0f, 40.0f, 8.0f, Color::RED };
		move4->renderData = ButtonRenderData{ 75.0f,  7.0f, 40.0f, 8.0f, Color::RED };

		fightScreen.addButton(move1);
		fightScreen.addButton(move2);
		fightScreen.addButton(move3);
		fightScreen.addButton(move4);

		m_overlays[MenuOverlay::ATTACK_SELECT] = fightScreen;
	}

	//	Battle Item Screen
	{
		Scene battleItemScreen(m_renderer);
		battleItemScreen.setBackgroundPath(g_sceneTextureLocations[MenuScene::BATTLE_ITEMS]);
		battleItemScreen.setReturnOverlay(MenuOverlay::BATTLE_OPTIONS);

		Button* upArrow = new Button;
		Button* item1 = new Button;
		Button* item2 = new Button;
		Button* item3 = new Button;
		Button* item4 = new Button;
		Button* item5 = new Button;
		Button* downArrow = new Button;

		TextBox* item1Name = new TextBox;
		TextBox* item2Name = new TextBox;
		TextBox* item3Name = new TextBox;
		TextBox* item4Name = new TextBox;
		TextBox* item5Name = new TextBox;

		TextBox* item1Amount = new TextBox;
		TextBox* item2Amount = new TextBox;
		TextBox* item3Amount = new TextBox;
		TextBox* item4Amount = new TextBox;
		TextBox* item5Amount = new TextBox;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		item1->data = 0;
		item2->data = 1;
		item3->data = 2;
		item4->data = 3;
		item5->data = 4;

		upArrow->text = "UP";
		item1Name->dynamic_text = &battleItemData->itemName.string1;
		item2Name->dynamic_text = &battleItemData->itemName.string2;
		item3Name->dynamic_text = &battleItemData->itemName.string3;
		item4Name->dynamic_text = &battleItemData->itemName.string4;
		item5Name->dynamic_text = &battleItemData->itemName.string5;
		downArrow->text = "DOWN";

		item1Amount->dynamic_text = &battleItemData->itemAmount.string1;
		item2Amount->dynamic_text = &battleItemData->itemAmount.string2;
		item3Amount->dynamic_text = &battleItemData->itemAmount.string3;
		item4Amount->dynamic_text = &battleItemData->itemAmount.string4;
		item5Amount->dynamic_text = &battleItemData->itemAmount.string5;


		upArrow->up = downArrow;
		upArrow->down = item1;

		item1->up = upArrow;
		item1->down = item2;

		item2->up = item1;
		item2->down = item3;

		item3->up = item2;
		item3->down = item4;

		item4->up = item3;
		item4->down = item5;

		item5->up = item4;
		item5->down = downArrow;

		downArrow->up = item5;
		downArrow->down = upArrow;

		float topX = 50.0f;
		float topY = 90.0f;

		float buttonGap = 13.0f;

		float width = 30.0f;
		float height = 10.0f;

		Color color = Color::BUTTER_SCOTCH;

		upArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 0), width, height, color };
		item1->renderData = ButtonRenderData{ topX, topY - (buttonGap * 1), width, height, color };
		item2->renderData = ButtonRenderData{ topX, topY - (buttonGap * 2), width, height, color };
		item3->renderData = ButtonRenderData{ topX, topY - (buttonGap * 3), width, height, color };
		item4->renderData = ButtonRenderData{ topX, topY - (buttonGap * 4), width, height, color };
		item5->renderData = ButtonRenderData{ topX, topY - (buttonGap * 5), width, height, color };
		downArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 6), width, height, color };

		float pixels = 20.0f;
		float innerOffset = 2.0f;

		//TODO: Make a texture render data
		//Images are what causes things to slow
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 1), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 2), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 3), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 4), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 5), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });

		item1Name->renderData = TextBoxRenderData{ topX - 10.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item2Name->renderData = TextBoxRenderData{ topX - 10.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item3Name->renderData = TextBoxRenderData{ topX - 10.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item4Name->renderData = TextBoxRenderData{ topX - 10.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item5Name->renderData = TextBoxRenderData{ topX - 10.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		item1Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item2Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item3Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item4Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item5Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };


		battleItemScreen.addTextBox(item1Name);
		battleItemScreen.addTextBox(item2Name);
		battleItemScreen.addTextBox(item3Name);
		battleItemScreen.addTextBox(item4Name);
		battleItemScreen.addTextBox(item5Name);

		battleItemScreen.addTextBox(item1Amount);
		battleItemScreen.addTextBox(item2Amount);
		battleItemScreen.addTextBox(item3Amount);
		battleItemScreen.addTextBox(item4Amount);
		battleItemScreen.addTextBox(item5Amount);

		battleItemScreen.addButton(upArrow);
		battleItemScreen.addButton(item1);
		battleItemScreen.addButton(item2);
		battleItemScreen.addButton(item3);
		battleItemScreen.addButton(item4);
		battleItemScreen.addButton(item5);
		battleItemScreen.addButton(downArrow);

		m_scenes[MenuScene::BATTLE_ITEMS] = battleItemScreen;
	}

	// Level Up Stats
	{
		Overlay levelUpStats{m_renderer};
		levelUpStats.setOverlayBackground(new ImageRenderData{ 75.0f, 30.0f, 20.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::LEVEL_UP_STAT_CHANGE] });

		TextBox* name = new TextBox();
		TextBox* level = new TextBox();
		TextBox* maxHP = new TextBox();
		TextBox* attack = new TextBox();
		TextBox* defense = new TextBox();
		TextBox* spAttack = new TextBox();
		TextBox* spDefense = new TextBox();
		TextBox* speed = new TextBox();

		name->dynamic_text = &battleData->pokemonStatName;
		level->dynamic_text = &battleData->pokemonStatLevel;

		maxHP->text = "MAX HP";
		attack->text = "ATTACK";
		defense->text = "DEFENSE";
		spAttack->text = "SP ATK";
		spDefense->text = "SP DEF";
		speed->text = "SPEED";


		name->renderData = TextBoxRenderData{75.0f, 47.0f, 5.0f};
		level->renderData = TextBoxRenderData{93.0f, 53.0f, 2.5f, Color::BLACK, Alignment::RIGHT_ALIGN};

		float xPos = 57.0f;
		float yPos = 38.0f;

		float yGap = 7.0f;
		float fontSize = 4.0f;

		Color textColor = Color::BLACK;

		Alignment textPosition = Alignment::LEFT_ALIGN;

		maxHP->renderData =		TextBoxRenderData{xPos, yPos - (0 * yGap), fontSize, textColor, textPosition};
		attack->renderData =	TextBoxRenderData{xPos, yPos - (1 * yGap), fontSize, textColor, textPosition};
		defense->renderData =	TextBoxRenderData{xPos, yPos - (2 * yGap), fontSize, textColor, textPosition};
		spAttack->renderData =	TextBoxRenderData{xPos, yPos - (3 * yGap), fontSize, textColor, textPosition};
		spDefense->renderData = TextBoxRenderData{xPos, yPos - (4 * yGap), fontSize, textColor, textPosition};
		speed->renderData =		TextBoxRenderData{xPos, yPos - (5 * yGap), fontSize, textColor, textPosition};

		levelUpStats.addTextBox(name);
		levelUpStats.addTextBox(level);
		levelUpStats.addTextBox(maxHP);
		levelUpStats.addTextBox(attack);
		levelUpStats.addTextBox(defense);
		levelUpStats.addTextBox(spAttack);
		levelUpStats.addTextBox(spDefense);
		levelUpStats.addTextBox(speed);

		m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE] = levelUpStats;
		m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE] = levelUpStats;

		// Stat Value Difference
		{
			TextBox* maxHPDiff = new TextBox();
			TextBox* attackDiff = new TextBox();
			TextBox* defenseDiff = new TextBox();
			TextBox* spAttackDiff = new TextBox();
			TextBox* spDefenseDiff = new TextBox();
			TextBox* speedDiff = new TextBox();

			maxHPDiff->dynamic_text = &battleData->pokemonStatDifference.string1;
			attackDiff->dynamic_text = &battleData->pokemonStatDifference.string2;
			defenseDiff->dynamic_text = &battleData->pokemonStatDifference.string3;
			spAttackDiff->dynamic_text = &battleData->pokemonStatDifference.string4;
			spDefenseDiff->dynamic_text = &battleData->pokemonStatDifference.string5;
			speedDiff->dynamic_text = &battleData->pokemonStatDifference.string6;

			maxHPDiff->renderData =		TextBoxRenderData{ 93.0f, yPos - (0 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};
			attackDiff->renderData =	TextBoxRenderData{ 93.0f, yPos - (1 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};
			defenseDiff->renderData =	TextBoxRenderData{ 93.0f, yPos - (2 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};
			spAttackDiff->renderData =	TextBoxRenderData{ 93.0f, yPos - (3 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};
			spDefenseDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (4 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};
			speedDiff->renderData =		TextBoxRenderData{ 93.0f, yPos - (5 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN};

			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(maxHPDiff);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(attackDiff);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(defenseDiff);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(spAttackDiff);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(spDefenseDiff);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_CHANGE].addTextBox(speedDiff);
		}

		// New Stat Values
		{
			TextBox* maxHPValue = new TextBox();
			TextBox* attackValue = new TextBox();
			TextBox* defenseValue = new TextBox();
			TextBox* spAttackValue = new TextBox();
			TextBox* spDefenseValue = new TextBox();
			TextBox* speedValue = new TextBox();

			maxHPValue->dynamic_text = &battleData->pokemonStatValue.string1;
			attackValue->dynamic_text = &battleData->pokemonStatValue.string2;
			defenseValue->dynamic_text = &battleData->pokemonStatValue.string3;
			spAttackValue->dynamic_text = &battleData->pokemonStatValue.string4;
			spDefenseValue->dynamic_text = &battleData->pokemonStatValue.string5;
			speedValue->dynamic_text = &battleData->pokemonStatValue.string6;

			maxHPValue->renderData =		TextBoxRenderData{ 93.0f, yPos - (0 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			attackValue->renderData =		TextBoxRenderData{ 93.0f, yPos - (1 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			defenseValue->renderData =		TextBoxRenderData{ 93.0f, yPos - (2 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spAttackValue->renderData =		TextBoxRenderData{ 93.0f, yPos - (3 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spDefenseValue->renderData =	TextBoxRenderData{ 93.0f, yPos - (4 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			speedValue->renderData =		TextBoxRenderData{ 93.0f, yPos - (5 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
		
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(maxHPValue);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(attackValue);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(defenseValue);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(spAttackValue);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(spDefenseValue);
			m_overlays[MenuOverlay::LEVEL_UP_STAT_VALUE].addTextBox(speedValue);
		}
		

	}

	logger->log(LogLevel::INFO, "Menu Scenes Setup", "setupScenes", "Menu");
}

void Menu::setupInteractionData(SharedString* items, std::string* balance)
{
	// Buy Item Scene
	{
		Scene buyItemScreem(m_renderer);

		Button* upArrow = new Button;
		Button* item1 = new Button;
		Button* item2 = new Button;
		Button* item3 = new Button;
		Button* item4 = new Button;
		Button* item5 = new Button;
		Button* item6 = new Button;
		Button* downArrow = new Button;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		item1->data = 0;
		item2->data = 1;
		item3->data = 2;
		item4->data = 3;
		item5->data = 4;
		item6->data = 5;

		upArrow->text = "UP ARROW";
		item1->dynamic_text = &items->string1;
		item2->dynamic_text = &items->string2;
		item3->dynamic_text = &items->string3;
		item4->dynamic_text = &items->string4;
		item5->dynamic_text = &items->string5;
		item6->dynamic_text = &items->string6;
		downArrow->text = "DOWN ARROW";

		upArrow->up = downArrow;
		upArrow->down = item1;

		item1->up = upArrow;
		item1->down = item2;

		item2->up = item1;
		item2->down = item3;

		item3->up = item2;
		item3->down = item4;

		item4->up = item3;
		item4->down = item5;

		item5->up = item4;
		item5->down = item6;

		item6->up = item5;
		item6->down = downArrow;

		downArrow->up = item6;
		downArrow->down = upArrow;

		buyItemScreem.addButton(upArrow);
		buyItemScreem.addButton(item1);
		buyItemScreem.addButton(item2);
		buyItemScreem.addButton(item3);
		buyItemScreem.addButton(item4);
		buyItemScreem.addButton(item5);
		buyItemScreem.addButton(item6);
		buyItemScreem.addButton(downArrow);

		TextBox* playerBalance = new TextBox;
		playerBalance->dynamic_text = balance;

		buyItemScreem.addTextBox(playerBalance);

		m_scenes[MenuScene::BUY_ITEMS] = buyItemScreem;
	}

	//PC Scene
	{
		Scene usePC(m_renderer);

		Button* leftArrow = new Button;
		Button* rightArrow = new Button;

		Button* boxTitle = new Button;
		Button* box1  = new Button;
		Button* box2  = new Button;
		Button* box3  = new Button;
		Button* box4  = new Button;
		Button* box5  = new Button;
		Button* box6  = new Button;
		Button* box7  = new Button;
		Button* box8  = new Button;
		Button* box9  = new Button;
		Button* box10 = new Button;
		Button* box11 = new Button;
		Button* box12 = new Button;
		Button* box13 = new Button;
		Button* box14 = new Button;
		Button* box15 = new Button;
		Button* box16 = new Button;
		Button* box17 = new Button;
		Button* box18 = new Button;
		Button* box19 = new Button;
		Button* box20 = new Button;
		Button* box21 = new Button;
		Button* box22 = new Button;
		Button* box23 = new Button;
		Button* box24 = new Button;
		Button* box25 = new Button;
		Button* box26 = new Button;
		Button* box27 = new Button;
		Button* box28 = new Button;
		Button* box29 = new Button;
		Button* box30 = new Button;
		Button* roster1 = new Button;
		Button* roster2 = new Button;
		Button* roster3 = new Button;
		Button* roster4 = new Button;
		Button* roster5 = new Button;
		Button* roster6 = new Button;
		

		leftArrow->data = arrowDirections::LEFT;
		rightArrow->data = arrowDirections::RIGHT;
		boxTitle->data = NONE;
		box1->data = 0;
		box2->data = 1;
		box3->data = 2;
		box4->data = 3;
		box5->data = 4;
		box6->data = 5;
		box7->data = 6;
		box8->data = 7;
		box9->data = 8;
		box10->data = 9;
		box11->data = 10;
		box12->data = 11;
		box13->data = 12;
		box14->data = 13;
		box15->data = 14;
		box16->data = 15;
		box17->data = 16;
		box18->data = 17;
		box19->data = 18;
		box20->data = 19;
		box21->data = 20;
		box22->data = 21;
		box23->data = 22;
		box24->data = 23;
		box25->data = 24;
		box26->data = 25;
		box27->data = 26;
		box28->data = 27;
		box29->data = 28;
		box30->data = 29;
		roster1->data = 30;
		roster2->data = 31;
		roster3->data = 32;
		roster4->data = 33;
		roster5->data = 34;
		roster6->data = 35;

		leftArrow->text = "Left Arrow";
		rightArrow->text = "Right Arrow";
		boxTitle->text = "Box Title";
		box1 ->text =  "Box 1";
		box2 ->text =  "Box 2";
		box3 ->text =  "Box 3";
		box4 ->text =  "Box 4";
		box5 ->text =  "Box 5";
		box6 ->text =  "Box 6";
		box7 ->text =  "Box 7";
		box8 ->text =  "Box 8";
		box9 ->text =  "Box 9";
		box10->text = "Box 10";
		box11->text = "Box 11";
		box12->text = "Box 12";
		box13->text = "Box 13";
		box14->text = "Box 14";
		box15->text = "Box 15";
		box16->text = "Box 16";
		box17->text = "Box 17";
		box18->text = "Box 18";
		box19->text = "Box 19";
		box20->text = "Box 20";
		box21->text = "Box 21";
		box22->text = "Box 22";
		box23->text = "Box 23";
		box24->text = "Box 24";
		box25->text = "Box 25";
		box26->text = "Box 26";
		box27->text = "Box 27";
		box28->text = "Box 28";
		box29->text = "Box 29";
		box30->text = "Box 30";
		roster1->text = "Roster 1";
		roster2->text = "Roster 2";
		roster3->text = "Roster 3";
		roster4->text = "Roster 4";
		roster5->text = "Roster 5";
		roster6->text = "Roster 6";

		leftArrow->down = box1;
		leftArrow->right = boxTitle;

		boxTitle->left = leftArrow;
		boxTitle->right = rightArrow;
		boxTitle->down = box3;

		rightArrow->left = boxTitle;
		rightArrow->down = box5;

		box1->up = boxTitle;
		box1->down = box6;
		box1->right = box2;

		box2->up = boxTitle;
		box2->down = box7;
		box2->left = box1;
		box2->right = box3;

		box3->up = boxTitle;
		box3->down = box8;
		box3->left = box2;
		box3->right = box4;

		box4->up = boxTitle;
		box4->down = box9;
		box4->left = box3;
		box4->right = box5;

		box5->up = boxTitle;
		box5->down = box10;
		box5->left = box4;
		box5->right = roster1;

		box6->up = box1;
		box6->down = box11;
		box6->right = box7;

		box7->up = box2;
		box7->down = box12;
		box7->left = box6;
		box7->right = box8;

		box8->up = box3;
		box8->down = box13;
		box8->left = box7;
		box8->right = box9;

		box9->up = box4;
		box9->down = box14;
		box9->left = box8;
		box9->right = box10;

		box10->up = box5;
		box10->down = box15;
		box10->left = box9;
		box10->right = roster1;

		box11->up = box6;
		box11->down = box16;
		box11->right = box12;

		box12->up = box7;
		box12->down = box17;
		box12->left = box11;
		box12->right = box13;

		box13->up = box8;
		box13->down = box18;
		box13->left = box12;
		box13->right = box14;

		box14->up = box9;
		box14->down = box19;
		box14->left = box13;
		box14->right = box15;

		box15->up = box10;
		box15->down = box20;
		box15->left = box14;
		box15->right = roster3;

		box16->up = box11;
		box16->down = box21;
		box16->right = box17;

		box17->up = box12;
		box17->down = box22;
		box17->left = box16;
		box17->right = box18;

		box18->up = box13;
		box18->down = box23;
		box18->left = box17;
		box18->right = box19;

		box19->up = box14;
		box19->down = box24;
		box19->left = box18;
		box19->right = box20;

		box20->up = box15;
		box20->down = box25;
		box20->left = box19;
		box20->right = roster3;

		box21->up = box16;
		box21->down = box26;
		box21->right = box22;

		box22->up = box17;
		box22->down = box27;
		box22->left = box22;
		box22->right = box23;

		box23->up = box18;
		box23->down = box28;
		box23->left = box22;
		box23->right = box24;

		box24->up = box19;
		box24->down = box29;
		box24->left = box23;
		box24->right = box25;

		box25->up = box20;
		box25->down = box30;
		box25->left = box24;
		box25->right = roster5;

		box26->up = box21;
		box26->right = box27;

		box27->up = box22;
		box27->left = box26;
		box27->right = box28;

		box28->up = box23;
		box28->left = box27;
		box28->right = box29;

		box29->up = box24;
		box29->left = box28;
		box29->right = box30;

		box30->up = box25;
		box30->left = box29;
		box30->right = roster5;

		roster1->down = roster3;
		roster1->left = box10;
		roster1->right = roster2;

		roster2->down = roster4;
		roster2->left = roster1;

		roster3->up = roster1;
		roster3->down = roster5;
		roster3->left = box15;
		roster3->right = roster4;

		roster4->up = roster2;
		roster4->down = roster6;
		roster4->left = roster3;

		roster5->up = roster3;
		roster5->left = box25;
		roster5->right = roster6;

		roster6->up = roster4;
		roster6->left = roster5;

		//TODO: Add the overlay for moving and viewing of stats
		//TODO: Add images to the buttons

		usePC.addButton(box1);
		usePC.addButton(box2);
		usePC.addButton(box3);
		usePC.addButton(box4);
		usePC.addButton(box5);
		usePC.addButton(box6);
		usePC.addButton(box7);
		usePC.addButton(box8);
		usePC.addButton(box9);
		usePC.addButton(box10);
		usePC.addButton(box11);
		usePC.addButton(box12);
		usePC.addButton(box13);
		usePC.addButton(box14);
		usePC.addButton(box15);
		usePC.addButton(box16);
		usePC.addButton(box17);
		usePC.addButton(box18);
		usePC.addButton(box19);
		usePC.addButton(box20);
		usePC.addButton(box21);
		usePC.addButton(box22);
		usePC.addButton(box23);
		usePC.addButton(box24);
		usePC.addButton(box25);
		usePC.addButton(box26);
		usePC.addButton(box27);
		usePC.addButton(box28);
		usePC.addButton(box29);
		usePC.addButton(box30);
		usePC.addButton(roster1);
		usePC.addButton(roster2);
		usePC.addButton(roster3);
		usePC.addButton(roster4);
		usePC.addButton(roster5);
		usePC.addButton(roster6);

		usePC.addButton(leftArrow);
		usePC.addButton(rightArrow);
		usePC.addButton(boxTitle);



		m_scenes[MenuScene::USE_PC] = usePC;
	}

}

void Menu::setupPauseData(SharedString* items, std::string* balance, std::string* time, RosterDisplayData* rosterData, TrainerBadgeData* badgeData, PauseSettingsData* settingData)
{
	// Pause Main Menu
	{
		Scene pauseMainMenu(m_renderer);
		pauseMainMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_MENU]);

		TextBox* playerBalance = new TextBox();
		playerBalance->dynamic_text = balance;
		playerBalance->renderData = TextBoxRenderData{ 2.0f, 74.4f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN};

		TextBox* playTime = new TextBox();
		playTime->dynamic_text = time;
		playTime->renderData = TextBoxRenderData{ 98.0f, 74.4f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

		pauseMainMenu.addTextBox(playerBalance);
		pauseMainMenu.addTextBox(playTime);

		// Option Buttons
		{
			Button* pokemonRoster = new Button;
			Button* bagOfItems = new Button;
			Button* mapView = new Button;
			Button* changeSettings = new Button;
			Button* saveGame = new Button;
			Button* exitGame = new Button;

			//TODO: Probably dont hard code these but also i dont care
			pokemonRoster->data = 0;
			bagOfItems->data = 1;
			mapView->data = 2;
			changeSettings->data = 3;
			saveGame->data = 4;
			exitGame->data = 5;


			pokemonRoster->down = mapView;
			pokemonRoster->right = bagOfItems;

			bagOfItems->down = changeSettings;
			bagOfItems->left = pokemonRoster;

			mapView->up = pokemonRoster;
			mapView->down = saveGame;
			mapView->right = changeSettings;

			changeSettings->up = bagOfItems;
			changeSettings->left = mapView;
			changeSettings->down = exitGame;

			saveGame->up = mapView;
			saveGame->right = exitGame;

			exitGame->up = changeSettings;
			exitGame->left = saveGame;


			pokemonRoster->text = "ROSTER";
			bagOfItems->text = "BAG";
			mapView->text = "MAP";
			changeSettings->text = "SETTINGS";
			saveGame->text = "SAVE";
			exitGame->text = "EXIT";

			pokemonRoster->renderData = { 27.5f, 66.0f,	25.0f, 18.0f, Color::BLUE };
			bagOfItems->renderData = { 72.5, 66.0f,		25.0f, 18.0f, Color::BLUE };
			mapView->renderData = { 27.5f, 41.0f,		25.0f, 18.0f, Color::BLUE };
			changeSettings->renderData = { 72.5, 41.0f,	25.0f, 18.0f, Color::BLUE };
			saveGame->renderData = { 27.5f, 16.0f,		25.0f, 18.0f, Color::BLUE };
			exitGame->renderData = { 72.5f, 16.0f,		25.0f, 18.0f, Color::BLUE };

			pokemonRoster->scene = MenuScene::PAUSE_ROSTER;
			changeSettings->scene = MenuScene::PAUSE_SETTINGS;
			bagOfItems->scene = MenuScene::PAUSE_BAG;

			pauseMainMenu.addButton(pokemonRoster);
			pauseMainMenu.addButton(bagOfItems);
			pauseMainMenu.addButton(mapView);
			pauseMainMenu.addButton(changeSettings);
			pauseMainMenu.addButton(saveGame);
			pauseMainMenu.addButton(exitGame);
		}

		// Badge Images
		{
			//31% 70

			pauseMainMenu.addImage(new ImageRenderData{ (309.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/normalBadge.png",	nullptr, &badgeData->normalBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (365.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/waterBadge.png",	nullptr, &badgeData->waterBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (421.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/rockBadge.png",		nullptr, &badgeData->rockBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (477.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/flyingBadge.png",	nullptr, &badgeData->flyingBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (533.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/grassBadge.png",	nullptr, &badgeData->grassBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (589.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/iceBadge.png",		nullptr, &badgeData->iceBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (645.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/fireBadge.png",		nullptr, &badgeData->fireBadgeVisibility});
			pauseMainMenu.addImage(new ImageRenderData{ (701.0f/1000.0f) * 100.0f, (493.5f/563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/dragonBadge.png",	nullptr, &badgeData->dragonBadgeVisibility});
		}
		
		
		m_scenes[MenuScene::PAUSE_MENU] = pauseMainMenu;
	}


	// Pause Roster Menu
	{
		Scene pauseRosterMenu(m_renderer);
		pauseRosterMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_ROSTER]);

		Button* roster1 = new Button;
		Button* roster2 = new Button;
		Button* roster3 = new Button;
		Button* roster4 = new Button;
		Button* roster5 = new Button;
		Button* roster6 = new Button;

		roster1->data = 0;
		roster2->data = 1;
		roster3->data = 2;
		roster4->data = 3;
		roster5->data = 4;
		roster6->data = 5;


		roster1->down = roster2;

		roster2->up = roster1;
		roster2->down = roster3;

		roster3->up = roster2;
		roster3->down = roster4;

		roster4->up = roster3;
		roster4->down = roster5;

		roster5->up = roster4;
		roster5->down = roster6;

		roster6->up = roster5;

		roster1->renderData = {50.0f, 89.5f, 33.0f, 10.8f, Color::BLUE};
		roster2->renderData = {50.0f, 73.7f, 33.0f, 10.8f, Color::BLUE};
		roster3->renderData = {50.0f, 57.9f, 33.0f, 10.8f, Color::BLUE};
		roster4->renderData = {50.0f, 42.1f, 33.0f, 10.8f, Color::BLUE};
		roster5->renderData = {50.0f, 26.3f, 33.0f, 10.8f, Color::BLUE};
		roster6->renderData = {50.0f, 10.5f, 33.0f, 10.8f, Color::BLUE};

		pauseRosterMenu.addButton(roster1);
		pauseRosterMenu.addButton(roster2);
		pauseRosterMenu.addButton(roster3);
		pauseRosterMenu.addButton(roster4);
		pauseRosterMenu.addButton(roster5);
		pauseRosterMenu.addButton(roster6);

		TextBox* pokemonName = new TextBox();
		TextBox* pokemonLevel = new TextBox();
		TextBox* pokemonHealth = new TextBox();

		// Roster Data
		{
			TextBox* pokemon1Name = new TextBox();
			TextBox* pokemon2Name = new TextBox();
			TextBox* pokemon3Name = new TextBox();
			TextBox* pokemon4Name = new TextBox();
			TextBox* pokemon5Name = new TextBox();
			TextBox* pokemon6Name = new TextBox();

			TextBox* pokemon1level = new TextBox();
			TextBox* pokemon2level = new TextBox();
			TextBox* pokemon3level = new TextBox();
			TextBox* pokemon4level = new TextBox();
			TextBox* pokemon5level = new TextBox();
			TextBox* pokemon6level = new TextBox();

			TextBox* pokemon1hp = new TextBox();
			TextBox* pokemon2hp = new TextBox();
			TextBox* pokemon3hp = new TextBox();
			TextBox* pokemon4hp = new TextBox();
			TextBox* pokemon5hp = new TextBox();
			TextBox* pokemon6hp = new TextBox();



			pokemon1Name->dynamic_text = &rosterData->pokemon1.name;
			pokemon2Name->dynamic_text = &rosterData->pokemon2.name;
			pokemon3Name->dynamic_text = &rosterData->pokemon3.name;
			pokemon4Name->dynamic_text = &rosterData->pokemon4.name;
			pokemon5Name->dynamic_text = &rosterData->pokemon5.name;
			pokemon6Name->dynamic_text = &rosterData->pokemon6.name;

			pokemon1level->dynamic_text = &rosterData->pokemon1.level;
			pokemon2level->dynamic_text = &rosterData->pokemon2.level;
			pokemon3level->dynamic_text = &rosterData->pokemon3.level;
			pokemon4level->dynamic_text = &rosterData->pokemon4.level;
			pokemon5level->dynamic_text = &rosterData->pokemon5.level;
			pokemon6level->dynamic_text = &rosterData->pokemon6.level;

			pokemon1hp->dynamic_text = &rosterData->pokemon1.hp;
			pokemon2hp->dynamic_text = &rosterData->pokemon2.hp;
			pokemon3hp->dynamic_text = &rosterData->pokemon3.hp;
			pokemon4hp->dynamic_text = &rosterData->pokemon4.hp;
			pokemon5hp->dynamic_text = &rosterData->pokemon5.hp;
			pokemon6hp->dynamic_text = &rosterData->pokemon6.hp;

			pokemon1Name->renderData = TextBoxRenderData{66.0f, 89.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon2Name->renderData = TextBoxRenderData{66.0f, 73.7f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon3Name->renderData = TextBoxRenderData{66.0f, 57.9f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon4Name->renderData = TextBoxRenderData{66.0f, 42.1f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon5Name->renderData = TextBoxRenderData{66.0f, 26.3f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon6Name->renderData = TextBoxRenderData{66.0f, 10.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};

			pokemon1level->renderData = TextBoxRenderData{33.5f, 83.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};
			pokemon2level->renderData = TextBoxRenderData{33.5f, 67.7f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};
			pokemon3level->renderData = TextBoxRenderData{33.5f, 51.9f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};
			pokemon4level->renderData = TextBoxRenderData{33.5f, 36.1f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};
			pokemon5level->renderData = TextBoxRenderData{33.5f, 20.3f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};
			pokemon6level->renderData = TextBoxRenderData{33.5f,  4.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN};

			pokemon1hp->renderData = TextBoxRenderData{66.5f, 83.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon2hp->renderData = TextBoxRenderData{66.5f, 67.7f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon3hp->renderData = TextBoxRenderData{66.5f, 51.9f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon4hp->renderData = TextBoxRenderData{66.5f, 36.1f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon5hp->renderData = TextBoxRenderData{66.5f, 20.3f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};
			pokemon6hp->renderData = TextBoxRenderData{66.5f,  4.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN};

			pauseRosterMenu.addTextBox(pokemon1Name);
			pauseRosterMenu.addTextBox(pokemon2Name);
			pauseRosterMenu.addTextBox(pokemon3Name);
			pauseRosterMenu.addTextBox(pokemon4Name);
			pauseRosterMenu.addTextBox(pokemon5Name);
			pauseRosterMenu.addTextBox(pokemon6Name);

			pauseRosterMenu.addTextBox(pokemon1level);
			pauseRosterMenu.addTextBox(pokemon2level);
			pauseRosterMenu.addTextBox(pokemon3level);
			pauseRosterMenu.addTextBox(pokemon4level);
			pauseRosterMenu.addTextBox(pokemon5level);
			pauseRosterMenu.addTextBox(pokemon6level);

			pauseRosterMenu.addTextBox(pokemon1hp);
			pauseRosterMenu.addTextBox(pokemon2hp);
			pauseRosterMenu.addTextBox(pokemon3hp);
			pauseRosterMenu.addTextBox(pokemon4hp);
			pauseRosterMenu.addTextBox(pokemon5hp);
			pauseRosterMenu.addTextBox(pokemon6hp);

			float pixels = 15.0f;
			float innerOffset = 2.0f;

			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 91.5f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 75.7f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 59.9f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 44.1f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 28.3f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 12.5f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });

			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 91.5f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon1.pokemonTexture});
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 75.7f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon2.pokemonTexture});
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 59.9f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon3.pokemonTexture});
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 44.1f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon4.pokemonTexture});
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 28.3f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon5.pokemonTexture});
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 12.5f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon6.pokemonTexture});
		
		
		}

		// Static Text
		{
			TextBox* typeTextBox = new TextBox();
			TextBox* hpTextBox = new TextBox();
			TextBox* attackTextBox = new TextBox();
			TextBox* defenseTextBox = new TextBox();
			TextBox* spAttackTextBox = new TextBox();
			TextBox* spDefenseTextBox = new TextBox();
			TextBox* speedTextBox = new TextBox();


			typeTextBox->text = "Type";
			hpTextBox->text = "HP";
			attackTextBox->text = "Attack";
			defenseTextBox->text = "Defense";
			spAttackTextBox->text = "SpAttack";
			spDefenseTextBox->text = "spDefense";
			speedTextBox->text = "Speed";

			typeTextBox->renderData = TextBoxRenderData{ 0.0f,		(408.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			hpTextBox->renderData = TextBoxRenderData{ 0.0f,							 62.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			attackTextBox->renderData = TextBoxRenderData{ 0.0f,	(253.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			defenseTextBox->renderData = TextBoxRenderData{ 0.0f,	(213.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			spAttackTextBox->renderData = TextBoxRenderData{ 0.0f,	(173.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			spDefenseTextBox->renderData = TextBoxRenderData{ 0.0f,	(133.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			speedTextBox->renderData = TextBoxRenderData{ 0.0f,		( 93.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			pauseRosterMenu.addTextBox(typeTextBox);
			pauseRosterMenu.addTextBox(hpTextBox);
			pauseRosterMenu.addTextBox(attackTextBox);
			pauseRosterMenu.addTextBox(defenseTextBox);
			pauseRosterMenu.addTextBox(spAttackTextBox);
			pauseRosterMenu.addTextBox(spDefenseTextBox);
			pauseRosterMenu.addTextBox(speedTextBox);
		}

		// Left Side Data
		{
			TextBox* attack = new TextBox();
			TextBox* defense = new TextBox();
			TextBox* spAttack = new TextBox();
			TextBox* spDefense = new TextBox();
			TextBox* speed = new TextBox();

			attack->dynamic_text = &rosterData->pausePokemonData.attack;
			defense->dynamic_text = &rosterData->pausePokemonData.defense;
			spAttack->dynamic_text = &rosterData->pausePokemonData.spAttack;
			spDefense->dynamic_text = &rosterData->pausePokemonData.spDefense;
			speed->dynamic_text = &rosterData->pausePokemonData.speed;

			attack->renderData = TextBoxRenderData{ 33.0f,		(253.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			defense->renderData = TextBoxRenderData{ 33.0f,		(213.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			spAttack->renderData = TextBoxRenderData{ 33.0f,		(173.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			spDefense->renderData = TextBoxRenderData{ 33.0f,	(133.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			speed->renderData = TextBoxRenderData{ 33.0f,		(93.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			pauseRosterMenu.addTextBox(attack);
			pauseRosterMenu.addTextBox(defense);
			pauseRosterMenu.addTextBox(spAttack);
			pauseRosterMenu.addTextBox(spDefense);
			pauseRosterMenu.addTextBox(speed);

			pauseRosterMenu.addRectangle(new RectangleRenderData{ 13.7f, (338.0f / 563.0f) * 100.0f, (11.0f / 563.0f) * 100.0f, &rosterData->pausePokemonData.hpPercent});
		}

		// Move Data
		{
			TextBox* moveText = new TextBox();

			TextBox* move1Name = new TextBox();
			TextBox* move2Name = new TextBox();
			TextBox* move3Name = new TextBox();
			TextBox* move4Name = new TextBox();

			TextBox* currentPP1 = new TextBox();
			TextBox* currentPP2 = new TextBox();
			TextBox* currentPP3 = new TextBox();
			TextBox* currentPP4 = new TextBox();

			TextBox* maxPP1 = new TextBox();
			TextBox* maxPP2 = new TextBox();
			TextBox* maxPP3 = new TextBox();
			TextBox* maxPP4 = new TextBox();

			moveText->text = "MOVES";

			move1Name->dynamic_text = &rosterData->pausePokemonData.move1.moveName;
			move2Name->dynamic_text = &rosterData->pausePokemonData.move2.moveName;
			move3Name->dynamic_text = &rosterData->pausePokemonData.move3.moveName;
			move4Name->dynamic_text = &rosterData->pausePokemonData.move4.moveName;

			currentPP1->dynamic_text = &rosterData->pausePokemonData.move1.currentPP;
			currentPP2->dynamic_text = &rosterData->pausePokemonData.move2.currentPP;
			currentPP3->dynamic_text = &rosterData->pausePokemonData.move3.currentPP;
			currentPP4->dynamic_text = &rosterData->pausePokemonData.move4.currentPP;

			maxPP1->dynamic_text = &rosterData->pausePokemonData.move1.maxPP;
			maxPP2->dynamic_text = &rosterData->pausePokemonData.move2.maxPP;
			maxPP3->dynamic_text = &rosterData->pausePokemonData.move3.maxPP;
			maxPP4->dynamic_text = &rosterData->pausePokemonData.move4.maxPP;

			moveText->renderData = TextBoxRenderData{ 84.0f, (473.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK };

			move1Name->renderData = TextBoxRenderData{ 73.0f, (373.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move2Name->renderData = TextBoxRenderData{ 73.0f, (283.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move3Name->renderData = TextBoxRenderData{ 73.0f, (193.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move4Name->renderData = TextBoxRenderData{ 73.0f, (103.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			currentPP1->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP2->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP3->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP4->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			maxPP1->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP2->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP3->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP4->renderData = TextBoxRenderData{ (880.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };


			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (353.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move1.moveTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (263.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move2.moveTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (173.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move3.moveTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (83.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move4.moveTextureLocation });

			pauseRosterMenu.addTextBox(moveText);

			pauseRosterMenu.addTextBox(move1Name);
			pauseRosterMenu.addTextBox(move2Name);
			pauseRosterMenu.addTextBox(move3Name);
			pauseRosterMenu.addTextBox(move4Name);

			pauseRosterMenu.addTextBox(currentPP1);
			pauseRosterMenu.addTextBox(currentPP2);
			pauseRosterMenu.addTextBox(currentPP3);
			pauseRosterMenu.addTextBox(currentPP4);

			pauseRosterMenu.addTextBox(maxPP1);
			pauseRosterMenu.addTextBox(maxPP2);
			pauseRosterMenu.addTextBox(maxPP3);
			pauseRosterMenu.addTextBox(maxPP4);
		}

		pokemonName->dynamic_text = &rosterData->pausePokemonData.name;
		pokemonLevel->dynamic_text = &rosterData->pausePokemonData.level;
		pokemonHealth->dynamic_text = &rosterData->pausePokemonData.health;

		pokemonName->renderData = TextBoxRenderData{ 15.0f, 82.0f, 4.0f, Color::BLACK };
		pokemonLevel->renderData = TextBoxRenderData{ 20.1f, 91.3f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonHealth->renderData = TextBoxRenderData{ 20.0f, 61.0f, 5.0f, Color::BLACK };

		pauseRosterMenu.addTextBox(pokemonName);
		pauseRosterMenu.addTextBox(pokemonLevel);
		pauseRosterMenu.addTextBox(pokemonHealth);

		
		pauseRosterMenu.addImage(new ImageRenderData{ 15.0f, 75.0f, 5.0f, 2.5f, "", &rosterData->pausePokemonData.type1 });	//TODO: Doesnt need to be heap allocated
		pauseRosterMenu.addImage(new ImageRenderData{ 25.0f, 75.0f, 5.0f, 2.5f, "", &rosterData->pausePokemonData.type2 });	//TODO: Doesnt need to be heap allocated

		m_scenes[MenuScene::PAUSE_ROSTER] = pauseRosterMenu;

		Scene battleRoster = pauseRosterMenu;
		battleRoster.setReturnOverlay(MenuOverlay::BATTLE_OPTIONS);
		m_scenes[MenuScene::BATTLE_ROSTER] = battleRoster;
	}

	// Change Control Overlay
	{
		Overlay changeInput(m_renderer);
		changeInput.setOverlayBackground(new ImageRenderData{ 50.0f, 55.0f, 30.0f, 15.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

		TextBox* pressNewKey = new TextBox();

		pressNewKey->text = "PRESS NEW INPUT";

		pressNewKey->renderData = TextBoxRenderData{ 50.0f, 50.0f, 5.0f };

		changeInput.addTextBox(pressNewKey);
		m_overlays[MenuOverlay::CHANGE_INPUT] = changeInput;
	}

	// Pause Settings Menu
	{
		Scene pauseControlsMenu(m_renderer);
		pauseControlsMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_SETTINGS]);

		float buttonY = (float)56.57193606;			// Correct
		float heightGap = (float)5.328596803f;			// Correct
		float widthGap = 8.2f;					// Correct

		float keyboardX = 18.7f;				// Correct
		float generalX = 60.0f;					// Kinda TODO: Correct for Resolution
		float controllerX = 85.3f;				// Correct

		float buttonWidth = 4.25f;				// Correct
		float buttonHeight = 2.4f;				// Correct

		Button* keyboardUpMain		= new Button;
		Button* keyboardUpAlt		= new Button;
		Button* keyboardDownMain	= new Button;
		Button* keyboardDownAlt		= new Button;	
		Button* keyboardLeftMain	= new Button;
		Button* keyboardLeftAlt		= new Button;
		Button* keyboardRightMain	= new Button;
		Button* keyboardRightAlt	= new Button;	
		Button* keyboardSelectMain	= new Button;
		Button* keyboardSelectAlt	= new Button;
		Button* keyboardBackMain	= new Button;
		Button* keyboardBackAlt		= new Button;
		Button* keyboardPauseMain	= new Button;
		Button* keyboardPauseAlt	= new Button;
		Button* keyboardSprintMain	= new Button;	
		Button* keyboardSprintAlt	= new Button;

		Button* controllerUpMain		= new Button;
		Button* controllerUpAlt			= new Button;
		Button* controllerDownMain		= new Button;
		Button* controllerDownAlt		= new Button;
		Button* controllerLeftMain		= new Button;
		Button* controllerLeftAlt		= new Button;
		Button* controllerRightMain		= new Button;
		Button* controllerRightAlt		= new Button;
		Button* controllerSelectMain	= new Button;
		Button* controllerSelectAlt		= new Button;
		Button* controllerBackMain		= new Button;
		Button* controllerBackAlt		= new Button;
		Button* controllerPauseMain		= new Button;
		Button* controllerPauseAlt		= new Button;
		Button* controllerSprintMain	= new Button;
		Button* controllerSprintAlt		= new Button;

		Button* generalResolution	= new Button;
		Button* generalFullscreen	= new Button;
		Button* generalShowFps		= new Button;
		Button* generalAutoSave		= new Button;
		Button* generalFasterText	= new Button;

		// Keyboard Buttons
		{

			// Data
			{
				keyboardUpMain->data = 0;
				keyboardUpAlt->data = 1;
				keyboardDownMain->data = 2;
				keyboardDownAlt->data = 3;
				keyboardLeftMain->data = 4;
				keyboardLeftAlt->data = 5;
				keyboardRightMain->data = 6;
				keyboardRightAlt->data = 7;
				keyboardSelectMain->data = 8;
				keyboardSelectAlt->data = 9;
				keyboardBackMain->data = 10;
				keyboardBackAlt->data = 11;
				keyboardPauseMain->data = 12;
				keyboardPauseAlt->data = 13;
				keyboardSprintMain->data = 14;
				keyboardSprintAlt->data = 15;
			}

			// Text
			{
				keyboardUpMain		->dynamic_text = &settingData->keyboardData.UpMain;
				keyboardUpAlt		->dynamic_text = &settingData->keyboardData.UpAlt;
				keyboardDownMain	->dynamic_text = &settingData->keyboardData.DownMain;
				keyboardDownAlt		->dynamic_text = &settingData->keyboardData.DownAlt;
				keyboardLeftMain	->dynamic_text = &settingData->keyboardData.LeftMain;
				keyboardLeftAlt		->dynamic_text = &settingData->keyboardData.LeftAlt;
				keyboardRightMain	->dynamic_text = &settingData->keyboardData.RightMain;
				keyboardRightAlt	->dynamic_text = &settingData->keyboardData.RightAlt;
				keyboardSelectMain	->dynamic_text = &settingData->keyboardData.SelectMain;
				keyboardSelectAlt	->dynamic_text = &settingData->keyboardData.SelectAlt;
				keyboardBackMain	->dynamic_text = &settingData->keyboardData.BackMain;
				keyboardBackAlt		->dynamic_text = &settingData->keyboardData.BackAlt;
				keyboardPauseMain	->dynamic_text = &settingData->keyboardData.PauseMain;
				keyboardPauseAlt	->dynamic_text = &settingData->keyboardData.PauseAlt;
				keyboardSprintMain	->dynamic_text = &settingData->keyboardData.SprintMain;
				keyboardSprintAlt	->dynamic_text = &settingData->keyboardData.SprintAlt;

			}

			// Link
			{
			keyboardUpMain->down = keyboardDownMain;
			keyboardUpMain->right = keyboardUpAlt;

			keyboardDownMain->up = keyboardUpMain;
			keyboardDownMain->down = keyboardLeftMain;
			keyboardDownMain->right = keyboardDownAlt;

			keyboardLeftMain->up = keyboardDownMain;
			keyboardLeftMain->down = keyboardRightMain;
			keyboardLeftMain->right = keyboardLeftAlt;

			keyboardRightMain->up = keyboardLeftMain;
			keyboardRightMain->down = keyboardSelectMain;
			keyboardRightMain->right = keyboardRightAlt;

			keyboardSelectMain->up = keyboardRightMain;
			keyboardSelectMain->down = keyboardBackMain;
			keyboardSelectMain->right = keyboardSelectAlt;

			keyboardBackMain->up = keyboardSelectMain;
			keyboardBackMain->down = keyboardPauseMain;
			keyboardBackMain->right = keyboardBackAlt;

			keyboardPauseMain->up = keyboardBackMain;
			keyboardPauseMain->down = keyboardSprintMain;
			keyboardPauseMain->right = keyboardPauseAlt;

			keyboardSprintMain->up = keyboardPauseMain;
			keyboardSprintMain->right = keyboardSprintAlt;


			keyboardUpAlt->down = keyboardDownAlt;
			keyboardUpAlt->left = keyboardUpMain;
			keyboardUpAlt->right = generalResolution;

			keyboardDownAlt->up = keyboardUpAlt;
			keyboardDownAlt->down = keyboardLeftAlt;
			keyboardDownAlt->left = keyboardDownMain;
			keyboardDownAlt->right = generalFullscreen;

			keyboardLeftAlt->up = keyboardDownAlt;
			keyboardLeftAlt->down = keyboardRightAlt;
			keyboardLeftAlt->left = keyboardLeftMain;
			keyboardLeftAlt->right = generalShowFps;

			keyboardRightAlt->up = keyboardLeftAlt;
			keyboardRightAlt->down = keyboardSelectAlt;
			keyboardRightAlt->left = keyboardRightMain;
			keyboardRightAlt->right = generalAutoSave;

			keyboardSelectAlt->up = keyboardRightAlt;
			keyboardSelectAlt->down = keyboardBackAlt;
			keyboardSelectAlt->left = keyboardSelectMain;
			keyboardSelectAlt->right = generalFasterText;

			keyboardBackAlt->up = keyboardSelectAlt;
			keyboardBackAlt->down = keyboardPauseAlt;
			keyboardBackAlt->left = keyboardBackMain;
			keyboardBackAlt->right = generalFasterText;

			keyboardPauseAlt->up = keyboardBackAlt;
			keyboardPauseAlt->down = keyboardSprintAlt;
			keyboardPauseAlt->left = keyboardPauseMain;
			keyboardPauseAlt->right = generalFasterText;

			keyboardSprintAlt->up = keyboardPauseAlt;
			keyboardSprintAlt->left = keyboardSprintMain;
			keyboardSprintAlt->right = generalFasterText;
			}

			// Render Data
			{
				keyboardUpMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 0), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardUpAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 0), buttonWidth, buttonHeight,		Color::WHITE };
				keyboardDownMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardDownAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardLeftMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardLeftAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardRightMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
				keyboardRightAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 3), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardSelectMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 4), buttonWidth, buttonHeight,Color::WHITE };
				keyboardSelectAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
				keyboardBackMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardBackAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardPauseMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 6), buttonWidth, buttonHeight, Color::WHITE };
				keyboardPauseAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 6), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardSprintMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 7), buttonWidth, buttonHeight,Color::WHITE };
				keyboardSprintAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 7), buttonWidth, buttonHeight, Color::WHITE };
			}

			// Overlay
			{
				keyboardUpMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardUpAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardDownMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardDownAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardLeftMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardLeftAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardRightMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardRightAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSelectMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSelectAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardBackMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardBackAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardPauseMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardPauseAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSprintMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSprintAlt->overlay = MenuOverlay::CHANGE_INPUT;
			}


		}

		// General Buttons

		{
			// Data
			{
				generalResolution->data = 16;
				generalFullscreen->data = 17;
				generalShowFps->data = 18;
				generalAutoSave->data = 19;
				generalFasterText->data = 20;

				generalResolution->overlay = MenuOverlay::RESOLUTION_SELECTION;
			}

			// Text
			{
				generalResolution->dynamic_text = &settingData->resolution;
				generalFullscreen->dynamic_text = &settingData->fullscreen;
				generalShowFps->dynamic_text = &settingData->showFps;
				generalAutoSave->dynamic_text = &settingData->autoSave;
				generalFasterText->dynamic_text = &settingData->fasterText;
			}

			// Link
			{
				generalResolution->left = keyboardUpAlt;
				generalResolution->down = generalFullscreen;
				generalResolution->right = controllerUpMain;

				generalFullscreen->up = generalResolution;
				generalFullscreen->down = generalShowFps;
				generalFullscreen->left = keyboardDownAlt;
				generalFullscreen->right = controllerDownMain;

				generalShowFps->up = generalFullscreen;
				generalShowFps->down = generalAutoSave;
				generalShowFps->left = keyboardLeftAlt;
				generalShowFps->right = controllerLeftMain;

				generalAutoSave->up = generalShowFps;
				generalAutoSave->left = keyboardRightAlt;
				generalAutoSave->down = generalFasterText;
				generalAutoSave->right = controllerRightMain;

				generalFasterText->up = generalAutoSave;
				generalFasterText->left = keyboardSelectAlt;
				generalFasterText->right = controllerSelectMain;
			}

			// Render Data
			{
				generalResolution->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - (heightGap * 0), buttonWidth * 2, buttonHeight, Color::WHITE};
				generalFullscreen->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 1), buttonWidth, buttonHeight, Color::WHITE };
				generalShowFps->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 2), buttonWidth, buttonHeight, Color::WHITE };
				generalAutoSave->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
				generalFasterText->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
			}

			// Pause Resolution Selection
			{
				Overlay resolutionSelection(m_renderer);
				resolutionSelection.setOverlayBackground(new ImageRenderData{ generalX - (buttonWidth / 2.0f), buttonY - (heightGap * 1), buttonWidth + (buttonWidth / 2.0f), buttonHeight * 2, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

				Button* resolutionSmall = new Button;
				Button* resolutionMedium = new Button;
				Button* resolutionLarge = new Button;

				resolutionSmall->text = "1280x720";
				resolutionMedium->text = "1920x1080";
				resolutionLarge->text = "2560x1440";

				resolutionSmall->data = RendererResolutiion::_1280x720;
				resolutionMedium->data = RendererResolutiion::_1920x1080;
				resolutionLarge->data = RendererResolutiion::_2560x1440;

				resolutionSmall->down = resolutionMedium;
				resolutionMedium->up = resolutionSmall;
				resolutionMedium->down = resolutionLarge;
				resolutionLarge->up = resolutionMedium;

				resolutionSmall->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 1), buttonWidth * 2, buttonHeight, Color::WHITE };
				resolutionMedium->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 2), buttonWidth * 2, buttonHeight, Color::WHITE };
				resolutionLarge->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 3), buttonWidth * 2, buttonHeight, Color::WHITE };

				resolutionSelection.addButton(resolutionSmall);
				resolutionSelection.addButton(resolutionMedium);
				resolutionSelection.addButton(resolutionLarge);

				m_overlays[MenuOverlay::RESOLUTION_SELECTION] = resolutionSelection;
			}
		}
		

		// Controller Buttons
		{

			// Data
			{
				controllerUpMain->data = 21;
				controllerUpAlt->data = 22;
				controllerDownMain->data = 23;
				controllerDownAlt->data = 24;
				controllerLeftMain->data = 25;
				controllerLeftAlt->data = 26;
				controllerRightMain->data = 27;
				controllerRightAlt->data = 28;
				controllerSelectMain->data = 29;
				controllerSelectAlt->data = 30;
				controllerBackMain->data = 31;
				controllerBackAlt->data = 32;
				controllerPauseMain->data = 33;
				controllerPauseAlt->data = 34;
				controllerSprintMain->data = 35;
				controllerSprintAlt->data = 36;
			}

			// Text
			{
				controllerUpMain->dynamic_text		= &settingData->controllerData.UpMain;
				controllerUpAlt->dynamic_text		= &settingData->controllerData.UpAlt;
				controllerDownMain->dynamic_text	= &settingData->controllerData.DownMain;
				controllerDownAlt->dynamic_text		= &settingData->controllerData.DownAlt;
				controllerLeftMain->dynamic_text	= &settingData->controllerData.LeftMain;
				controllerLeftAlt->dynamic_text		= &settingData->controllerData.LeftAlt;
				controllerRightMain->dynamic_text	= &settingData->controllerData.RightMain;
				controllerRightAlt->dynamic_text	= &settingData->controllerData.RightAlt;
				controllerSelectMain->dynamic_text	= &settingData->controllerData.SelectMain;
				controllerSelectAlt->dynamic_text	= &settingData->controllerData.SelectAlt;
				controllerBackMain->dynamic_text	= &settingData->controllerData.BackMain;
				controllerBackAlt->dynamic_text		= &settingData->controllerData.BackAlt;
				controllerPauseMain->dynamic_text	= &settingData->controllerData.PauseMain;
				controllerPauseAlt->dynamic_text	= &settingData->controllerData.PauseAlt;
				controllerSprintMain->dynamic_text	= &settingData->controllerData.SprintMain;
				controllerSprintAlt->dynamic_text	= &settingData->controllerData.SprintAlt;
			}

			// Link
			{
				controllerUpMain->down		= controllerDownMain;
				controllerUpMain->right		= controllerUpAlt;
				controllerUpMain->left		= generalResolution;

				controllerDownMain->up		= controllerUpMain;
				controllerDownMain->down	= controllerLeftMain;
				controllerDownMain->right	= controllerDownAlt;
				controllerDownMain->left	= generalFullscreen;

				controllerLeftMain->up		= controllerDownMain;
				controllerLeftMain->down	= controllerRightMain;
				controllerLeftMain->right	= controllerLeftAlt;
				controllerLeftMain->left	= generalShowFps;

				controllerRightMain->up		= controllerLeftMain;
				controllerRightMain->down	= controllerSelectMain;
				controllerRightMain->right	= controllerRightAlt;
				controllerRightMain->left	= generalAutoSave;

				controllerSelectMain->up	= controllerRightMain;
				controllerSelectMain->down	= controllerBackMain;
				controllerSelectMain->right = controllerSelectAlt;
				controllerSelectMain->left	= generalFasterText;

				controllerBackMain->up		= controllerSelectMain;
				controllerBackMain->down	= controllerPauseMain;
				controllerBackMain->right	= controllerBackAlt;
				controllerBackMain->left	= generalFasterText;

				controllerPauseMain->up		= controllerBackMain;
				controllerPauseMain->down	= controllerSprintMain;
				controllerPauseMain->right	= controllerPauseAlt;
				controllerPauseMain->left	= generalFasterText;

				controllerSprintMain->up	= controllerPauseMain;
				controllerSprintMain->right = controllerSprintAlt;
				controllerSprintMain->left = generalFasterText;
				
				controllerUpAlt->down = controllerDownAlt;
				controllerUpAlt->left = controllerUpMain;
				
				controllerDownAlt->up = controllerUpAlt;
				controllerDownAlt->down = controllerLeftAlt;
				controllerDownAlt->left = controllerDownMain;
				
				controllerLeftAlt->up = controllerDownAlt;
				controllerLeftAlt->down = controllerRightAlt;
				controllerLeftAlt->left = controllerLeftMain;
				
				controllerRightAlt->up = controllerLeftAlt;
				controllerRightAlt->down = controllerSelectAlt;
				controllerRightAlt->left = controllerRightMain;
				
				controllerSelectAlt->up = controllerRightAlt;
				controllerSelectAlt->down = controllerBackAlt;
				controllerSelectAlt->left = controllerSelectMain;
				
				controllerBackAlt->up = controllerSelectAlt;
				controllerBackAlt->down = controllerPauseAlt;
				controllerBackAlt->left = controllerBackMain;
				
				controllerPauseAlt->up = controllerBackAlt;
				controllerPauseAlt->down = controllerSprintAlt;
				controllerPauseAlt->left = controllerPauseMain;
				
				controllerSprintAlt->up = controllerPauseAlt;
				controllerSprintAlt->left = controllerSprintMain;
			}

			// Render Data
			{
			controllerUpMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 0), buttonWidth, buttonHeight,	Color::WHITE };
			controllerUpAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 0), buttonWidth, buttonHeight,		Color::WHITE };
			controllerDownMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
			controllerDownAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
			controllerLeftMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
			controllerLeftAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
			controllerRightMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
			controllerRightAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 3), buttonWidth, buttonHeight,	Color::WHITE };
			controllerSelectMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 4), buttonWidth, buttonHeight,Color::WHITE };
			controllerSelectAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
			controllerBackMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
			controllerBackAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
			controllerPauseMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 6), buttonWidth, buttonHeight, Color::WHITE };
			controllerPauseAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 6), buttonWidth, buttonHeight,	Color::WHITE };
			controllerSprintMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 7), buttonWidth, buttonHeight,Color::WHITE };
			controllerSprintAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 7), buttonWidth, buttonHeight, Color::WHITE };
			}

			{
				controllerUpMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerUpAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerDownMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerDownAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerLeftMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerLeftAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerRightMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerRightAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSelectMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSelectAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerBackMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerBackAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerPauseMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerPauseAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSprintMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSprintAlt->overlay = MenuOverlay::CHANGE_INPUT;

			}
		}


		pauseControlsMenu.addButton(generalResolution);
		pauseControlsMenu.addButton(generalFullscreen);
		pauseControlsMenu.addButton(generalShowFps);
		pauseControlsMenu.addButton(generalAutoSave);
		pauseControlsMenu.addButton(generalFasterText);
		pauseControlsMenu.addButton(keyboardUpMain);
		pauseControlsMenu.addButton(keyboardUpAlt);
		pauseControlsMenu.addButton(keyboardUpMain);
		pauseControlsMenu.addButton(keyboardUpAlt);
		pauseControlsMenu.addButton(keyboardDownMain);
		pauseControlsMenu.addButton(keyboardDownAlt);
		pauseControlsMenu.addButton(keyboardLeftMain);
		pauseControlsMenu.addButton(keyboardLeftAlt);
		pauseControlsMenu.addButton(keyboardRightMain);
		pauseControlsMenu.addButton(keyboardRightAlt);
		pauseControlsMenu.addButton(keyboardSelectMain);
		pauseControlsMenu.addButton(keyboardSelectAlt);
		pauseControlsMenu.addButton(keyboardBackMain);
		pauseControlsMenu.addButton(keyboardBackAlt);
		pauseControlsMenu.addButton(keyboardPauseMain);
		pauseControlsMenu.addButton(keyboardPauseAlt);
		pauseControlsMenu.addButton(keyboardSprintMain);
		pauseControlsMenu.addButton(keyboardSprintAlt);
		pauseControlsMenu.addButton(controllerUpMain);
		pauseControlsMenu.addButton(controllerUpAlt);
		pauseControlsMenu.addButton(controllerUpMain);
		pauseControlsMenu.addButton(controllerUpAlt);
		pauseControlsMenu.addButton(controllerDownMain);
		pauseControlsMenu.addButton(controllerDownAlt);
		pauseControlsMenu.addButton(controllerLeftMain);
		pauseControlsMenu.addButton(controllerLeftAlt);
		pauseControlsMenu.addButton(controllerRightMain);
		pauseControlsMenu.addButton(controllerRightAlt);
		pauseControlsMenu.addButton(controllerSelectMain);
		pauseControlsMenu.addButton(controllerSelectAlt);
		pauseControlsMenu.addButton(controllerBackMain);
		pauseControlsMenu.addButton(controllerBackAlt);
		pauseControlsMenu.addButton(controllerPauseMain);
		pauseControlsMenu.addButton(controllerPauseAlt);
		pauseControlsMenu.addButton(controllerSprintMain);
		pauseControlsMenu.addButton(controllerSprintAlt);

		m_scenes[MenuScene::PAUSE_SETTINGS] = pauseControlsMenu;
	}

	


	// Bag
	{
		Scene pauseBagMenu(m_renderer);

		Button* upArrow = new Button;
		Button* downArrow = new Button;

		Button* bagIndex0 = new Button;
		Button* bagIndex1 = new Button;
		Button* bagIndex2 = new Button;
		Button* bagIndex3 = new Button;
		Button* bagIndex4 = new Button;
		Button* bagIndex5 = new Button;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		bagIndex0->data = 0;
		bagIndex1->data = 1;
		bagIndex2->data = 2;
		bagIndex3->data = 3;
		bagIndex4->data = 4;
		bagIndex5->data = 5;


		upArrow->up = downArrow;
		upArrow->down = bagIndex0;


		bagIndex0->up = upArrow;
		bagIndex0->down = bagIndex1;

		bagIndex1->up = bagIndex0;
		bagIndex1->down = bagIndex2;

		bagIndex2->up = bagIndex1;
		bagIndex2->down = bagIndex3;

		bagIndex3->up = bagIndex2;
		bagIndex3->down = bagIndex4;

		bagIndex4->up = bagIndex3;
		bagIndex4->down = bagIndex5;

		bagIndex5->up = bagIndex4;
		bagIndex5->down = downArrow;

		downArrow->up = bagIndex5;
		downArrow->down = upArrow;


		upArrow->text = "Up Arrow";
		downArrow->text = "Down Arrow";
		bagIndex0->dynamic_text = &items->string1;
		bagIndex1->dynamic_text = &items->string2;
		bagIndex2->dynamic_text = &items->string3;
		bagIndex3->dynamic_text = &items->string4;
		bagIndex4->dynamic_text = &items->string5;
		bagIndex5->dynamic_text = &items->string6;


		pauseBagMenu.addButton(bagIndex0);
		pauseBagMenu.addButton(bagIndex1);
		pauseBagMenu.addButton(bagIndex2);
		pauseBagMenu.addButton(bagIndex3);
		pauseBagMenu.addButton(bagIndex4);
		pauseBagMenu.addButton(bagIndex5);
		pauseBagMenu.addButton(upArrow);
		pauseBagMenu.addButton(downArrow);

		m_scenes[MenuScene::PAUSE_BAG] = pauseBagMenu;
	}
}

void Menu::setscene(MenuScene scene)
{
	m_currentScene = scene;
	m_renderer->loadBackground(m_scenes[m_currentScene].getBackgroundPath());
}

void Menu::setOverlay(MenuOverlay overlay)
{
	m_currentOverlay = overlay;
	m_overlays[m_currentOverlay].reset();
}

void Menu::run()
{

	onUpdate();

	if (m_inputVariables->up)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goUp();
		else
			m_overlays[m_currentOverlay].goUp();
	}

	if (m_inputVariables->down)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goDown();
		else
			m_overlays[m_currentOverlay].goDown();
	}

	if (m_inputVariables->left)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goLeft();
		else
			m_overlays[m_currentOverlay].goLeft();
	}

	if (m_inputVariables->right)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goRight();
		else
			m_overlays[m_currentOverlay].goRight();
	}

	if (m_inputVariables->interact)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			handleSelection(m_scenes[m_currentScene].getSelection());
		else
			handleSelection(m_overlays[m_currentOverlay].getSelection());
	}

	if (m_inputVariables->back)
		handleLeave();
	
}

void Menu::onUpdate()
{
	m_leaveRequested = false;

	renderMenu();

	m_renderer->onUpdate();
	m_input->onUpdate();
}

void Menu::renderMenu()
{
	if (m_currentScene != MenuScene::NONE)
		m_scenes[m_currentScene].onUpdate();

	if (m_currentOverlay != MenuOverlay::NONE)
		m_overlays[m_currentOverlay].onUpdate();
}

bool Menu::handleSelection(Button* button)
{
	logger->log(LogLevel::INFO, "Button Selected", "handleSelection", "Menu");

	if (button == nullptr)
		return false;

	if (m_currentOverlay == MenuOverlay::NONE)
	{
		switch (m_currentScene)
		{
		case MenuScene::BATTLE_ROSTER:
		case MenuScene::BATTLE_ITEMS:
			if (m_requestedData == nullptr)
				m_menuCommand->selection1 = button->data;
			else
				*m_requestedData = button->data;
			break;
		case MenuScene::USE_PC:
		case MenuScene::PAUSE_MENU:
		case MenuScene::PAUSE_ROSTER:
		case MenuScene::PAUSE_SETTINGS:
		case MenuScene::PAUSE_BAG:
		case MenuScene::STARTUP_SCENE:
			*m_requestedData = button->data;
			break;
		default:
			logger->log(LogLevel::ERROR, "Selected button has not been programmed for data", "handleSelection", "Menu");
			break;
		}
	}
	else
	{
		switch (m_currentOverlay)
		{


		case MenuOverlay::BATTLE_OPTIONS:

			if (button->data == SimulationType::ATTACK_SELECTED)
				m_menuCommand->type = SimulationType::ATTACK_SELECTED;
			else if (button->data == SimulationType::POKEMON_SELECTED)
				m_menuCommand->type = SimulationType::POKEMON_SELECTED;
			else if (button->data == SimulationType::ITEM_SELECTED)
				m_menuCommand->type = SimulationType::ITEM_SELECTED;
			else if (button->data == SimulationType::FLEE_SELECTED)
			{
				m_menuCommand->type = SimulationType::FLEE_SELECTED;
				m_menuCommand->selection1 = 0;
			}
			m_currentOverlay = MenuOverlay::NONE;
			break;
		case MenuOverlay::ATTACK_SELECT:
			m_menuCommand->selection1 = button->data;
			break;
		case MenuOverlay::DELETE_CONFIRMATION:
		case MenuOverlay::RESOLUTION_SELECTION:
		case MenuOverlay::CHANGE_INPUT:
			m_overlays[m_currentOverlay].reset();
			m_currentOverlay = MenuOverlay::NONE;

		case MenuOverlay::ON_SCREEN_KEYBOARD:
		default:
			*m_requestedData = button->data;
			break;
		}
	}

	// Switch Scene
	if (button->scene != MenuScene::NONE)
	{
		m_previousScreens.push_back(m_currentScene);
		setscene(button->scene);

		logger->log(LogLevel::INFO, "Switching Scene", "handleSelection", "Menu");
	}

	// Switch Overlay
	if (button->overlay != MenuOverlay::NONE)
		setOverlay(button->overlay);

	return false;	//TODO: Make void function
}

bool Menu::handleLeave()	//TODO: Also a void function
{
	m_leaveRequested = true;
	logger->log(LogLevel::INFO, "Leave Requested", "handleLeave", "Menu");

	if (m_currentOverlay != MenuOverlay::NONE && m_canLeave && m_currentOverlay != MenuOverlay::BATTLE_OPTIONS)
	{
		if (m_currentOverlay == MenuOverlay::ATTACK_SELECT)
			m_currentOverlay = MenuOverlay::BATTLE_OPTIONS;
		else
			m_currentOverlay = MenuOverlay::NONE;
		return true;
	}

	if (m_currentOverlay == MenuOverlay::NONE && m_canLeave && m_scenes[m_currentScene].getReturnOverlay() != MenuOverlay::NONE)
		m_currentOverlay = m_scenes[m_currentScene].getReturnOverlay();

	if (m_previousScreens.size() == 0 || !m_canLeave)
		return true;
	

	if (m_previousScreens.size() != 0)
	{
		setscene(m_previousScreens.at(m_previousScreens.size() - 1));
		m_previousScreens.pop_back();
		logger->log(LogLevel::DEBUG, "Switching to previous screen", "handleLeave", "Menu");
	}

	return false;
}
