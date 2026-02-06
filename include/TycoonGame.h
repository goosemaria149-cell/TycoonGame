#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Resource.h"
#include "Production.h"
#include "Building.h"
#include "GameConstants.h"


/// Persistent player state.
class Player
{
public:
    std::string name;
    std::map<ResourceType, Resource> resources;
    std::vector<std::unique_ptr<Production>> productions;
    std::vector<std::unique_ptr<Building>> buildings;
    float money;
    int reputation;
    float totalEarnings;
    float totalSpent;
    int achievements;
    bool hasStocksUnlocked = false;
};

/// Main game orchestrator (simulation + UI rendering).
class TycoonGame
{
public:
    TycoonGame();
    ~TycoonGame();

    /// Initializes runtime state and attempts to load a saved game.
    void Initialize();

    /// Advances simulation by `deltaTime` seconds.
    void Update(float deltaTime);
    /// Renders all game UI.
    void Render();

    /// Attempts to purchase a building of the requested type.
    [[nodiscard]] bool BuildStructure(BuildingType type);
    /// Attempts to start a production investment.
    [[nodiscard]] bool BeginProduction(ProductionType type);
    /// Attempts to sell an owned building.
    [[nodiscard]] bool SellStructure(int buildingIndex);
    void UpdateResources(float deltaTime);
    void UpdateEconomy(float deltaTime);
    /// Attempts to buy an amount of a resource.
    [[nodiscard]] bool BuyResource(ResourceType type, float amount);
    /// Attempts to sell an amount of a resource.
    [[nodiscard]] bool SellResource(ResourceType type, float amount);
    void UpdateReputation();
    /// Attempts to upgrade an owned building.
    [[nodiscard]] bool UpgradeBuilding(int buildingIndex);

    /// Saves the current game state to a binary file.
    [[nodiscard]] bool SaveGame(const std::string &filename = "savegame.json") const;
    /// Loads game state from a binary file.
    [[nodiscard]] bool LoadGame(const std::string &filename = "savegame.json");

    [[nodiscard]] const Player &GetPlayer() const { return m_player; }
    [[nodiscard]] float GetGameTime() const { return m_gameTime; }
    [[nodiscard]] bool IsPaused() const { return m_isPaused; }
    [[nodiscard]] float GetFPS() const { return m_fps; }

    // Setters
    void SetPaused(bool paused) { m_isPaused = paused; }

private:
    // Game state
    Player m_player;
    float m_gameTime;
    bool m_isPaused;
    float m_economyUpdateTimer;
    float m_resourceUpdateTimer;
    float m_reputationUpdateTimer;
    float m_maintenanceUpdateTimer;
    float m_lastFrameTime;
    float m_fps;
    int m_frameCount;
    float m_fpsUpdateTimer;

    // Helper functions
    void InitializeResources();
    void InitializeBuildingTypes();
    void InitializeProductionTypes();
    [[nodiscard]] float CalculateResourcePrice(ResourceType type) const;
    [[nodiscard]] float CalculateProductionMultiplier() const;

    // GUI rendering functions
    void RenderMainMenu();
    void RenderResourcesWindow();
    void RenderProductionWindow();
    void RenderPurchaseBuildingsWindow();
    void RenderBuildingsWindow();
    void RenderMarketWindow();
    void RenderStockWindow();
    void RenderStockUnlockButton();
};
