//Simone and Mildred
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

Color blendColors(const Color& color1, const Color& color2)
{
    return Color(
        (color1.r + color2.r) / 2,
        (color1.g + color2.g) / 2,
        (color1.b + color2.b) / 2
    );
}

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);
    
    vector<Vector2f> vertices;
    vector<Color> vertexColors; //Store colors for each vertex
    vector<pair<Vector2f, Color>> points; // Store points with their respective colors

    // Load the font for text
    Font font;
    if (!font.loadFromFile("Arial.ttf"))  // Replace with the correct path if necessary
    {
        cout << "Error loading font" << endl;
        return -1;
    }

    // Set up text to display instructions
    Text instructions("Click on 3 points for triangle vertices", font, 30);
    instructions.setPosition(10, 10);
    instructions.setFillColor(Color::White);

    Text prompt("then click on 4th point to start", font, 30);
    prompt.setPosition(10, 50);
    prompt.setFillColor(Color::White);

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the player's input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "The left button was pressed" << endl;
                    cout << "Mouse X: " << event.mouseButton.x << endl;
                    cout << "Mouse Y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        vertexColors.push_back(Color(rand() % 256, rand() % 256, rand() % 256));

                    }
                    else if (vertices.size() == 3 && points.size() == 0)
                    {
                        // Storing  4th click as the starting point
                        points.push_back({Vector2f(event.mouseButton.x, event.mouseButton.y), Color::White});
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            // generate more points for the chaos game algorithm
            Vector2f lastPoint = points.back().first;
            Color lastColor = points.back().second;
	    //select random vertex
            int randomVertexIndex = rand() % 3;  
            Vector2f randomVertex = vertices[randomVertexIndex];
            Color randomVertexColor = vertexColors[randomVertexIndex];
            
            // calculate midpoint between random vertex and last point
            Vector2f newPoint = (lastPoint + randomVertex) / 2.f;
            Color newColor = blendColors(lastColor, randomVertexColor);
	    //push back the newly generated coord.
            points.push_back({newPoint, newColor});
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Draw the vertices as blue squares
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(vertices[i]);
            rect.setFillColor(vertexColors[i]);
            window.draw(rect);
        }

        // Draw the chaos game points as red circles
        for (size_t i = 0; i < points.size(); ++i)
        {
            RectangleShape pointShape(Vector2f(2, 2));  // Smaller red dots
            pointShape.setPosition(points[i].first);
            pointShape.setFillColor(points[i].second);
            window.draw(pointShape);
        }

        // Draw all prompts and instructions
        window.draw(instructions);
        window.draw(prompt);

        window.display();
    }

    return 0;
}
