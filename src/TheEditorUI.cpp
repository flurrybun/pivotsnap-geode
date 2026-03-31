#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

#include "TheEditorUI.hpp"
#include "TheTransformControls.hpp"

using namespace geode::prelude;

bool TheEditorUI::init(LevelEditorLayer * lel) {
	if (!EditorUI::init(lel)) {
		return false;
	}

	auto method = Mod::get()->getSettingValue<std::string>("snap-method");
	if (method == "keybind") return true;

	auto menu = this->querySelector("editor-buttons-menu");
	if (!menu) return true;
	auto sprite = CCSprite::create("GJ_snapBtn_001.png"_spr);

	auto btn = CCMenuItemSpriteExtra::create(
		sprite,
		this,
		menu_selector(TheEditorUI::onSnapBtn)
	);
	btn->setPosition({79, 30});
	btn->setContentSize({20, 20});
	btn->setID("snap"_spr);
	btn->setVisible(false);

	menu->addChild(btn);
	menu->updateLayout();

	schedule(schedule_selector(TheEditorUI::updateSnapBtn));
	m_fields->snapBtn = btn;

	return true;
}

void TheEditorUI::onSnapBtn(CCObject * sender) {
	static_cast<TheTransformControls*>(m_transformControl)->performSnap(false);
}

void TheEditorUI::updateSnapBtn(float dt) {
	bool visible = m_transformControl->isVisible();
	m_fields->snapBtn->setVisible(visible);
}
