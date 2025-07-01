#include "GameWidget.h"
#include <FL/fl_draw.h> 
#include <FL/Fl.H>       

GameWidget::GameWidget(int x, int y, int w, int h, const char *l) : Fl_Group(x, y, w, h, l)
{
    m_box_person = new Fl_Box(x, y, w, h, l); // 初始化Fl_Box
    end();
    box(FL_NO_BOX);
    m_pmap = nullptr;
}

GameWidget::~GameWidget() noexcept
{
    delete m_box_person;
}

void GameWidget::draw()
{
    // Draw background (sky) - top two-thirds as yellow 
    fl_rectf(x(), y(), w(), h() * 2 / 3, FL_YELLOW);

    // Draw ground - bottom one-third as black
    fl_rectf(x(), y() + h() * 2 / 3, w(), h() / 3, FL_BLACK);

    if (m_pmap != nullptr) {
        for (size_t i = 0; i < m_pmap->get_size(); i++) {
            const auto& actor(m_pmap->get_at(i));
            
            // Calculate the top-left drawing coordinates for the entity's bounding box.
            // actor.x and actor.y are relative to the map's origin, which is assumed
            // to be aligned with the GameWidget's origin (x(), y()).
            int entity_drawing_x = x() + (int)actor.x;
            int entity_drawing_y = y() + (int)actor.y; 

            switch (actor.type) {
                case EntityType::Player: // Draw player as a black stick figure
                {
                    fl_color(FL_RED); // Set player color to red

                    // 以40x40为基准绘制stickman
                    // Head (10x10 pixels) - centered horizontally
                    fl_rectf(entity_drawing_x + 14, entity_drawing_y, 10, 10);
                    // Body (14x16 pixels) - below head
                    fl_rectf(entity_drawing_x + 12, entity_drawing_y + 10, 14, 16);
                    // Left Arm (4x14 pixels) - extending from left side of body
                    fl_rectf(entity_drawing_x + 8, entity_drawing_y + 10, 4, 14);
                    // Right Arm (4x14 pixels) - extending from right side of body
                    fl_rectf(entity_drawing_x + 26, entity_drawing_y + 10, 4, 14);
                    // Left Leg (6x12 pixels) - extending from bottom-left of body
                    fl_rectf(entity_drawing_x + 12, entity_drawing_y + 26, 6, 12);
                    // Right Leg (6x12 pixels) - extending from bottom-right of body
                    fl_rectf(entity_drawing_x + 20, entity_drawing_y + 26, 6, 12);
                    
                    break;
                }
                case EntityType::Wall: {
                    fl_color(FL_DARK_RED); // Walls will be dark red
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.width, actor.height);
                    break;
                }
                case EntityType::Door: {
                    fl_color(FL_GREEN); // Doors will be green
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.width, actor.height);
                    break;
                }
                case EntityType::Spike: {
                    fl_color(FL_MAGENTA); // Spikes will be magenta
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.width, actor.height);
                    break;
                }
                default:
                    // Handle any other entity types or do nothing for them
                    break;
            }
        }
    }
    // Call base class to draw children widgets if any (uncomment if applicable)
    // BaseClass::draw_children(); 
}