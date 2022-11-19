import Sandcore.World.Creature.MoveCondition;


namespace Sandcore {
	void MoveCondition::operator=(MoveCondition& another) {
		moveState = another.moveState;

		direction = another.direction;
	}

	MoveCondition::MoveCondition(Vector3D<double> direction, MoveState moveState) : direction(direction), moveState(moveState) {

	}
}