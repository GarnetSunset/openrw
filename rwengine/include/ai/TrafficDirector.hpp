#pragma once

#include <data/PathData.hpp>
#include "AIGraph.hpp"
#include "AIGraphNode.hpp"

#include <glm/glm.hpp>
#include <vector>

class GameObject;
class GameWorld;

class TrafficDirector
{
public:
	
	TrafficDirector(AIGraph* graph, GameWorld* world);
	
	std::vector< AIGraphNode* > findAvailableNodes(AIGraphNode::NodeType type, const glm::vec3& near, float radius);
	
	void setDensity(AIGraphNode::NodeType type, float density);

	/**
	 * Creates new traffic at available locations.
	 * @param center The area to spawn around
	 * @param radius the maximum distance to spawn in
	 * @param max The maximum number of traffic to create.
	 */
	std::vector<GameObject*> populateNearby( const glm::vec3& center, float radius, int maxSpawn = -1 );

	/**
	 * Sets the maximum number of pedestrians and cars in the traffic system
	 */
	void setPopulationLimits(int maxPeds, int maxCars);
	
private:
	AIGraph* graph;
	GameWorld* world;
	float pedDensity;
	float carDensity;
	int maximumPedestrians;
	int maximumCars;
};