
#ifndef STONECOLD_DATAAI_H
#define STONECOLD_DATAAI_H

#include <string>

//
// AI DATA
//
// Pre-Defined AI Strings that can be parsed into Decision Trees
// - Each Decision must correspond 1:1 with the AiDecision Enum (e.g.: AiDecision::NONE)
// - Each sequence of Decisions must end with a AiAction Enum (e.g.: AiAction::IDLE)
// - The whole string and each "tree-node", decision or action, must be wrapped in parentheses ( )
// - Every first "child-node" will be parsed as "Decision TRUE", every second as "Decision FALSE"
//
//				  EXAMPLE STRING AND TREE	
//				  (D1(D2(A1)(A2))(D3(A3)))
//						    D1
//						   /  \
//						  D2   D3
//						 /  \    \
//						A1   A2   A3
//
//			Action A1 if D1 = TRUE and D2 = TRUE
//			Action A2 if D1 = TRUE and D2 = FALSE
//			Action A3 if D1 = FALSE and D5 = TRUE
//
namespace StoneCold::Resources::Raw {

//
// Simple melee AI that:
// - Does nothing, if the player is not visible
// - Runs in to attack if the player is visible and close and its health is high
// - Runs away in case the player is close and its health gets low
//
static const auto meleeAIStr = std::string(R"meleeAI(
		(AiDecision::PLAYER_VISIBLE
			(AiDecision::PLAYER_CLOSE
				(AiDecision::HEALTH_LOW (AiAction::MOVE_OUT) (AiAction::ATTACK))
				(AiDecision::HEALTH_LOW (AiAction::IDLE) (AiAction::MOVE_IN))
			)
			(AiAction::IDLE)
		)
	)meleeAI");

}

#endif
