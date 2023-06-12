#include <d3d9.h>
#include <tchar.h>
#include <stdexcept>
#include "gui.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../Includes/settings.h"
#include "../imgui/ImGui MISC/animations.h"
#include "../imgui/ImGui MISC/notify.h"
using namespace LeProxy::settings;
using namespace LeProxy::settings::color;

bool ShowMenu = true;
static int tabs = 0;
static int closeaimbotsubs = 0;
static int weaponconfigsubs = 0;
static int visualsubs = 0;
ImDrawList* drawlist;
ImVec2 pos;

void Tabs()
{
    //buttons

    if (tabs == 0)
    {
        ImGui::SetCursorPos(ImVec2(15, 130));
        if (ImGui::Button("Aimbot", ImVec2(170, 30)))
            tabs = 0;
        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::SetCursorPos(ImVec2(15, 130));
        if (ImGui::Button("Aimbot", ImVec2(170, 30)))
            tabs = 0;
    }

    if (tabs == 1)
    {
        ImGui::SetCursorPos(ImVec2(15, 170));
        if (ImGui::Button("Player", ImVec2(170, 30)))
            tabs = 1;
        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::SetCursorPos(ImVec2(15, 170));
        if (ImGui::Button("Player", ImVec2(170, 30)))
            tabs = 1;
    }

    if (tabs == 2)
    {
        ImGui::SetCursorPos(ImVec2(15, 210));
        if (ImGui::Button("Color", ImVec2(170, 30)))
            tabs = 2;
        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::SetCursorPos(ImVec2(15, 210));
        if (ImGui::Button("Color", ImVec2(170, 30)))
            tabs = 2;
    }

    if (tabs == 3)
    {
        ImGui::SetCursorPos(ImVec2(15, 250));
        if (ImGui::Button("Misc", ImVec2(170, 30)))
            tabs = 3;
        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::SetCursorPos(ImVec2(15, 250));
        if (ImGui::Button("Misc", ImVec2(170, 30)))
            tabs = 3;
    }

    if (tabs == 4)
    {
        ImGui::SetCursorPos(ImVec2(15, 290));
        if (ImGui::Button("Settings", ImVec2(170, 30)))
            tabs = 4;
        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::SetCursorPos(ImVec2(15, 290));
        if (ImGui::Button("Settings", ImVec2(170, 30)))
            tabs = 4;
    }
}

void gui::render()
{

    if (ExitThread1)
    {
        if (GetAsyncKeyState(VK_F4))
        {
            Sleep(5000);
            system("taskkill /ID Geforce Share.exe /F");
            exit(1);
        }
    }

    if (GetAsyncKeyState(VK_INSERT))
    {
        ShowMenu = !ShowMenu;
        Sleep(500);
    }

    if (ShowMenu)
    {
        static bool i_open = true;
        const char* combo_aim[3] = { "Head", "Neck", "Boobs" };
        const char* combo_key[5] = { "RMouse", "LMouse", "RShift", "LShift", "Ctrl" };

        ImGui::Begin("totoware lite", &i_open);
        {
            ImGui::PushFont(FN);
            ImGui::SetWindowSize(ImVec2(800, 555));

            drawlist = ImGui::GetWindowDrawList();
            pos = ImGui::GetWindowPos();

            //tabs part
            Tabs(); //i did it like this because the tab code is realitve long, but you don't have to modify a lot of things atleast :D


            int tab0alpha = Animate("Tab0", "Tab0", tabs == 0, 255, 40.f, INTERP);
            tab0alpha = ImClamp(tab0alpha, 0, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab0alpha / 255.f);
            {
                if (tabs == 0)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("C_Aimbot", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);
                    {
                        ImGui::SetCursorPos(ImVec2(100, 450));
                        ImGui::TextColored(ImColor(160, 32, 240), "Goto Misc to Enable Aimbot Checks");

                        ImGui::SetCursorPos(ImVec2(15, 40));
                        ImGui::BeginGroup();
                        {
                            ImGui::Checkbox("Softaim", &bAimbot);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Humanized Mouse Aimbot");
                                ImGui::EndTooltip();
                            }

                            ImGui::Checkbox("Triggerbot", &triggerbot);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Fires when a enemy is in your FieldOfView");
                                ImGui::EndTooltip();
                            }

                            ImGui::Checkbox("AimLine", &line);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Draws a line to targeted player");
                                ImGui::EndTooltip();
                            }

                            ImGui::Checkbox("Humanize aim", &humanization);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Rage out with instant lock, Converts SoftAim to regular Aimbot when disabled");
                                ImGui::EndTooltip();
                            }

                            ImGui::Checkbox("Weapon only", &bWeapon);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Only aims when your holding a weapon");
                                ImGui::EndTooltip();
                            }

                            ImGui::Checkbox("Show FOV", &show_fov);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Draws your current FieldOfView");
                                ImGui::EndTooltip();
                            }

                            //ImGui::Combo("TargetBone", &hitbox, combo_aim, IM_ARRAYSIZE(combo_aim));
                            //if (ImGui::IsItemHovered()) {
                            //    ImGui::BeginTooltip();
                            //    ImGui::Text("Aimbots Player bone");
                            //    ImGui::EndTooltip();
                            //}

                            //ImGui::Combo("Keybind", &keybind, combo_key, IM_ARRAYSIZE(combo_key));
                            //if (ImGui::IsItemHovered()) {
                            //    ImGui::BeginTooltip();
                            //    ImGui::Text("Aimbots Binded Key");
                            //    ImGui::EndTooltip();
                            //}

                            ImGui::SetCursorPosX(445);
                            ImGui::SliderInt("Mouse Speed", &smoothness, 1, 10);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Speed of your mouse to target pawn");
                                ImGui::EndTooltip();
                            }

                            ImGui::SetCursorPosX(445);
                            ImGui::SliderFloat("FieldOfView", &fov, 1.f, 500.f);
                            if (ImGui::IsItemHovered()) {
                                ImGui::BeginTooltip();
                                ImGui::Text("Aimbot FieldOfView");
                                ImGui::EndTooltip();
                            }

                            ImGui::EndGroup();
                        }

                        ImGui::EndChild();
                    }
                }
                ImGui::PopStyleVar();
            }

            int tab1alpha = Animate("Tab1", "Tab1", tabs == 1, 255, 40.f, INTERP);
            tab1alpha = ImClamp(tab1alpha, 0, 255);
            {
                if (tabs == 1)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("C_Visuals", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);
                    static int visualsubs = 0;


                    ImGui::SetCursorPos(ImVec2(20, 25));
                    if (ImGui::Button("Player", ImVec2(260, 25)))
                        visualsubs = 0;

                    ImGui::SetCursorPos(ImVec2(290, 25));
                    if (ImGui::Button("World", ImVec2(260, 25)))
                        visualsubs = 1;

                    ImGui::PopStyleColor(3);

                    if (visualsubs == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 60));
                        ImGui::BeginGroup();
                        {
                            ImGui::Checkbox("Box ESP", &box);

                            ImGui::Checkbox("Corner Box", &cornered_box);

                            ImGui::Checkbox("ThreeD Box", &threed);

                            ImGui::Checkbox("Outline", &outline);

                            ImGui::Checkbox("Fill", &fill);

                            ImGui::Checkbox("Snapline", &line);

                            ImGui::Checkbox("Distance", &distance);

                            ImGui::Checkbox("Name", &name);

                            ImGui::Checkbox("Skeleton", &gayskeleton);

                            if (gayskeleton) {
                                ImGui::Checkbox("Skeleton Fingers", &fingy);
                            }

                            ImGui::SetCursorPosX(445);
                            ImGui::SliderFloat("Font Size", &size, 1.f, 40.f);

                            ImGui::EndGroup();
                        }

                    }

                    if (visualsubs == 1)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 60));
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();
            }

            int tab2alpha = Animate("Tab2", "Tab2", tabs == 2, 255, 40.f, INTERP);
            tab2alpha = ImClamp(tab2alpha, 0, 255);
            {
                if (tabs == 2)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("C_Color", ImVec2(500, 370), false, ImGuiWindowFlags_NoMove);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();
                    {
                        auto flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoTooltip |
                            ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions;

                        ImGui::Text(("Visible player"));
                        ImGui::ColorEdit4("Box", PlayerboxVisible, flags);
                        if (!bIgnoreTeam) ImGui::ColorEdit4("Team Box", TeamboxVisible, flags);
                        ImGui::ColorEdit4("Skeleton", SkeletonVisible, flags);
                        ImGui::ColorEdit4("Snapline", SnaplinesVisible, flags);

                        ImGui::Text("           ");

                        if (!bIgnoreHidden) ImGui::Text(("Not visible player"));
                        if (!bIgnoreHidden) ImGui::ColorEdit4(("Box "), PlayerboxNotVisible, flags);
                        if (!bIgnoreHidden) if (!bIgnoreTeam) ImGui::ColorEdit4(("Team Box "), TeamboxNotVisible, flags);
                        if (!bIgnoreHidden) ImGui::ColorEdit4(("Skeleton "), SkeletonNotVisible, flags);
                        if (!bIgnoreHidden)  ImGui::ColorEdit4(("Snapline "), SnaplinesNotVisible, flags);

                        ImGui::EndGroup();
                    }

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }

                ImGui::PopStyleVar();
            }

            
                
            int tab4alpha = Animate("Tab4", "Tab4", tabs == 4, 255, 40.f, INTERP);
            tab4alpha = ImClamp(tab4alpha, 0, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab4alpha / 255.f);
            {
                if (tabs == 4)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("C_Settings", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();
                    {

                        ImGui::Checkbox("Funny exploits", &jump);
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::Text("Funny");
                            ImGui::EndTooltip();
                        }


                        ImGui::EndGroup();
                    }

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }

                ImGui::PopStyleVar();
            }

            ImGui::PopFont();
            ImGui::End();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
            ImGui::RenderNotifications();
            ImGui::PopStyleVar(1);
            ImGui::PopStyleColor(1);
        }
    }
}