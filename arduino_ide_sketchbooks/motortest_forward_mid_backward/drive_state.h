//! possible program states
enum DriveState
{
  StopAfterBackwardMovement = 0,
  ForwardAccelerate = 1,
  ForwardDecelerate = 2,
  StopAfterForwardMovement = 3,
  BackwardAccelerate = 4,
  BackwardDecelerate = 5,
};

//! Defines transitions from the current drive state to the next drive state.
DriveState transition(DriveState currentDriveState)
{
  switch(currentDriveState)
  {
  case DriveState::StopAfterBackwardMovement:
    Serial.println("=================");
    Serial.println("ForwardAccelerate");
    Serial.println("=================");
    return DriveState::ForwardAccelerate;
  case DriveState::ForwardAccelerate:
    Serial.println("=================");
    Serial.println("ForwardDecelerate");
    Serial.println("=================");
    return DriveState::ForwardDecelerate;
  case DriveState::ForwardDecelerate:
    Serial.println("========================");
    Serial.println("StopAfterForwardMovement");
    Serial.println("========================");
    return DriveState::StopAfterForwardMovement;
  case DriveState::StopAfterForwardMovement:
    Serial.println("==================");
    Serial.println("BackwardAccelerate");
    Serial.println("==================");
    return DriveState::BackwardAccelerate;
  case DriveState::BackwardAccelerate:
    Serial.println("==================");
    Serial.println("BackwardDecelerate");
    Serial.println("==================");
    return DriveState::BackwardDecelerate;
  case DriveState::BackwardDecelerate:
    Serial.println("=========================");
    Serial.println("StopAfterBackwardMovement");
    Serial.println("=========================");
    return DriveState::StopAfterBackwardMovement;
  }
  Serial.println("=====================");
  Serial.println("ERROR: INVALID STATE!");
  Serial.println("=====================");
  return DriveState::StopAfterBackwardMovement;
}
