/**********************************************************************************************
*
*   RLGameGUi * A game gui for raylib
*
*   LICENSE: MIT
*
*   Copyright (c) 2022 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "gui_screen.h"
#include "raylib.h"

namespace RLGameGUI
{
	bool GUIScreen::IsActive() const
	{
		return Active;
	}

	void GUIScreen::Activate()
	{
		Active = true;
		DoResize();
		OnActivate();
	}

	void GUIScreen::Deactivate()
	{
		Active = false;
		OnDeactivate();
	}

	void GUIScreen::DoResize()
    {
        Root.Resize();
        for (auto child : Elements)
            child->Resize();
	}

	void GUIScreen::Update()
	{
		PostRenderCallbacks.clear();

		if (IsWindowResized())
			DoResize();

		// do input
		Vector2 mouse = GetMousePosition();

		// let everyone think
		for (auto child : Elements)
			child->Update(mouse);
	}

	void GUIScreen::Render()
	{
		OnRender();
        for (auto child : Elements)
            child->Render();

		for (auto& callback : PostRenderCallbacks)
			callback();
	}

    GUIElement::Ptr GUIScreen::AddElement(GUIElement::Ptr element)
    {
		element->Parent = &Root;
		Elements.emplace_back(element);
		OnElementAdd(element);

		return element;
    }
}