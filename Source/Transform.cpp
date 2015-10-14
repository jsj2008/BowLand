#include "Transform.hpp"
#include <iostream>

using namespace DirectX;

// Constructor
Transform::Transform(GameObject* gameObj)
    : Component(gameObj)
{
    InitializeTransform(DirectX::XMFLOAT3(+0.0f, +0.0f, +0.0f));
    _gameObject->SetWorldMatrixDirty();
}

// Destructor
Transform::~Transform(){ }

// Initialize starting values for Position, Scale, and Rotation
void Transform::InitializeTransform(XMFLOAT3 nPos){
    _position = nPos;
    _scale = DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f);
    _rotation = DirectX::XMFLOAT3(+0.0f, +0.0f, +0.0f);
}

// Copy another transform into this one
void Transform::CopyTransform(Transform* nTra){
    _position = nTra->GetPosition();
    _scale = nTra->GetScale();
    _rotation = nTra->GetRotation();
    _gameObject->SetWorldMatrixDirty();
}

// Set the position
void Transform::SetPosition(XMFLOAT3 nPos){
    _position = nPos;
    _gameObject->SetWorldMatrixDirty();
}

// Set the scale
void Transform::SetScale(XMFLOAT3 nSca){
    _scale = nSca;
    _gameObject->SetWorldMatrixDirty();
}

// Set the roattion
void Transform::SetRotation(XMFLOAT3 nRot){
    _rotation = nRot;
    _gameObject->SetWorldMatrixDirty();
}

// Get the position
XMFLOAT3 Transform::GetPosition() const{
    return _position;
}

// Get the scale
XMFLOAT3 Transform::GetScale() const{
    return _scale;
}

// Get the rotation
XMFLOAT3 Transform::GetRotation() const{
    return _rotation;
}

// Get the position pointer
XMFLOAT3* Transform::GetPositionPtr()
{
    return &_position;
}

// Get the scale pointer
XMFLOAT3* Transform::GetScalePtr()
{
    return &_scale;
}

// Get the rotation pointer
XMFLOAT3* Transform::GetRotationPtr()
{
    return &_rotation;
}

void Transform::Update(const GameTime& gameTime){
    
}