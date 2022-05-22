#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
using namespace std;

struct background
{
	int r ;
	int g ;
	int b ;

};
int main()
{

	int from = 0;
	
	//background color changer
	const int count = 3;
	int r = 0;
	int b = 0;
	int g = 0;
	int color_index = 0;

	vector<background>bg(count);
	for(int i = 0 ;i<count;i++)
	{
		struct background c;
		bg.push_back(c);
	}
	
	bg[0].r = 0;bg[0].g = 0;bg[0].b = 0;
	bg[1].r = 112;bg[1].g = 66;bg[1].b =  20;
	bg[2].r = 208;bg[2].g = 196;bg[2].b = 160;

	

	//get the characters
	string s;
	cout<<"Enter The String For its punched tape\n";
	getline(cin,s);


	//Setting font 
	sf::Font font;
	if(!font.loadFromFile("Akshar-Light.ttf")){cout<<"Could not locate font";return 0;}

	//Main things of sfml
	
	sf::ContextSettings settings;
	settings.antialiasingLevel =8;
	sf::RenderWindow window(sf::VideoMode(800,600),"Punched Tape",sf::Style::Default,settings);
	while(window.isOpen())
	{
		//Basic event system 
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				window.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if((from+1)<s.length())from++;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if((from-1)>=0)from--;
			}

			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				color_index = (color_index+1)%count;
				r = bg[color_index].r;	
				g = bg[color_index].g;
				b = bg[color_index].b;

			}
			
			
		}

		window.clear(sf::Color(r,g,b));
		
		

		//Draw punched paper

		sf::RectangleShape paper(sf::Vector2f(330.f,600.f));
		paper.setPosition(260, 0);
		paper.setFillColor(sf::Color::White);
		window.draw(paper);


		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Black);

		//How to draw width of bits and height between two character bits
		int p_x = 280;
		int d_x = 35;
		int d_y = 35;
		int p_y = 90;
		
		//Draw Title
		text.setPosition(370,25);
		text.setString("7-bit punch");
		window.draw(text);

		for(int i = from;i<s.length();i++)
		{
			unsigned int x = s[i];
			vector<int>bin;
			while(x>0)
			{
				bin.insert(bin.begin(),x%2);
				x = x/2;
			}

			if(bin.size()<7)
			{
				for(int j= 0 ;j<7-bin.size();j++)
				{
					bin.insert(bin.begin(),0);
				}
			}
			
			for(int j = 0;j<bin.size();j++)
			{
				if(j==4)
				{

				sf::CircleShape bit(5.0f);
				bit.setFillColor(sf::Color(r,g,b));
				bit.setPosition(p_x,p_y+3);
				window.draw(bit);
				p_x+=d_x;
				}

				if(bin[j]==1){
				sf::CircleShape bit(10.0f);
				bit.setFillColor(sf::Color(r,g,b));
				bit.setPosition(p_x,p_y);
				window.draw(bit);
				}

				p_x+=d_x;

			}

			//Draw ascii of bin value

			text.setPosition(p_x,p_y-15);
			text.setString(s[i]);
			window.draw(text);

			p_x = 280;
			p_y +=d_y;
		}
		window.display();
	}

}
