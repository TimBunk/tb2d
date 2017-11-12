#include "playerHud.h"

PlayerHud::PlayerHud(ResourceManager* rm, Camera* camera) : Scene::Scene(camera) {
	// Initialize the variables
	this->rm = rm;
	showCase = new ShowCase(700, 500, 50, 50, camera, rm->GetShader("hud"), rm->GetShader("textHud"), rm->GetTexture("showCase"));
	this->AddChild(showCase);
	textGold = new Text("fonts/OpenSans-Regular.ttf", "Gold: 0", 60, glm::vec4(0.62f, 0.62f, 0.62f, 1.0f), true, camera, rm->GetShader("textHud"));
	textGold->localPosition = glm::vec3(20, 100, 1.0f);
	this->AddChild(textGold);
	textStats = new Text("fonts/OpenSans-Regular.ttf", "No stats available", 22, glm::vec4(0.62f, 0.62f, 0.62f, 1.0f), true, camera, rm->GetShader("textHud"));
	textStats->localPosition = glm::vec3(20, 500, 1.0f);
	this->AddChild(textStats);
}

PlayerHud::~PlayerHud() {
	delete showCase;
	delete textGold;
	delete textStats;
	for (unsigned int i=0;i<hudHealth.size();i++) {
		delete hudHealth[i];
	}
}

void PlayerHud::UpdateStats(std::string text) {
	textStats->SetText(text);
}

void PlayerHud::UpdateGold(int amount) {
	// Make a string out of the amount and set it as a text for the textGold
	std::string s = std::to_string(amount);
	std::string ss = "Gold: " + s;
	textGold->SetText(ss);
}

void PlayerHud::UpdateHealth(int currentHealth) {
	// Sets filled heart for every hudHealth that is lower then the currentHealth the others get a empty heart
	for (unsigned int i=0;i<hudHealth.size();i++) {
		if (currentHealth > i) {
			hudHealth[i]->SetTexture(rm->GetTexture("heartFilled"));
		}
		else {
			hudHealth[i]->SetTexture(rm->GetTexture("heartEmpty"));
		}
	}
}

void PlayerHud::GiveShowcase(ShowCaseItem sci) {
	showCase->Give(sci);
}

bool PlayerHud::IsShowCaseFull() {
	return showCase->IsFull();
}

void PlayerHud::ClearShowcase() {
	showCase->Clear();
}

void PlayerHud::CreateLives(int currentHealth, int health) {
	// Delete the old hearts
	std::vector<Hud*>::iterator it = hudHealth.begin();
	while (it != hudHealth.end()) {
		this->RemoveChild((*it));
		delete (*it);
		it = hudHealth.erase(it);
	}
	// Create the health hearts
	int xHealth = 30;
	for (int i=0;i<health;i++) {
		hudHealth.push_back(new Hud(xHealth, 30, 50, 50, camera, rm->GetShader("hud"), rm->GetTexture("heartFilled")));
		if (currentHealth-1 < i) {
			hudHealth[i]->SetTexture(rm->GetTexture("heartEmpty"));
		}
		this->AddChild(hudHealth[i]);
		xHealth += 60;
	}
}
