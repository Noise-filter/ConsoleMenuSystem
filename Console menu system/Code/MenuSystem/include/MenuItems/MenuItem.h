#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "Utility.h"
#include "Graphics.h"
#include "InputEvent.h"

namespace MenuSystem
{
	enum MenuItemType
	{
		MenuItemType_TextLabel,
		MenuItemType_Button,
		MenuItemType_Checkbox,
		MenuItemType_List,
		MenuItemType_CheckboxList,
		MenuItemType_ProgressBar,
		MenuItemType_InputField,
		MenuItemType_InputFieldPassword,
		MenuItemType_DrawArea,
		MenuItem_Sprite,

		MenuItemType_Count,
		MenuItemType_Unknown = -1
	};

	namespace MenuItem
	{
		class MenuItem
		{
		public:
			MenuItem(Utility::Pos pos = Utility::Pos());
			virtual ~MenuItem() = default;

			virtual void Render() = 0;
			virtual bool Update(InputEvent input) = 0;

			virtual void SetVisible(bool visible);
			void SetPosition(const Utility::Pos& pos);
			virtual void SetActive(const bool active);

			bool IsActive();
			unsigned int GetID();
			bool GetVisible();
			Utility::Pos& GetPosition();
			virtual MenuItemType GetType() = 0;
			virtual bool IsInteractive() const = 0;

			bool operator ==(const MenuItem& obj);
			bool operator !=(const MenuItem& obj);

		protected:
			const unsigned int ID;
			static unsigned int currentID;

			Utility::Pos pos;
			bool active;
			bool visible;
		};

	}
}

#endif