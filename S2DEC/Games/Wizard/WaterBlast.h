#pragma once
#include "Spell.h"

using namespace S2D;

class WaterBlast : public Spell {
private:

public:
	WaterBlast(sf::Vector2f position, sf::Vector2f endPosition, void* ui) : Spell(position, endPosition, SpellType::Water) {
		Spell::image.setSize(sf::Vector2f{ image.getSize().x,image.getSize().y * 2.5f });
		Spell::image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		this->ui = ui;
	}


	void update(float frameTime) override {
		Spell::update(frameTime);
	}

	void draw(sf::RenderTarget& target) override {
		Spell::draw(target);
	}
};