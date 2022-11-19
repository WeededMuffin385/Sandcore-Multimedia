export module Sandcore.World.Creature.MoveCondition;

import Sandcore.Vector3D;

export namespace Sandcore {
	enum class MoveState : char {
		sneak,
		move,
		run,
	};

	class MoveCondition {
	public:
		MoveCondition(Vector3D<double> direction = { 0,0,0 }, MoveState moveState = MoveState::move);
		void operator=(MoveCondition& another);

		/// <param name= "x">[-1; 1] (left/right)</param> 
		/// <param name= "y">[-1; 1] (forward/backward)</param>
		/// <param name= "z">[-1; 1] (up/down)</param>
		Vector3D<double> direction;

		MoveState moveState; // убрать MoveState заменить на unsigned double [0;2] чтобы контролировать скорость
	};
}