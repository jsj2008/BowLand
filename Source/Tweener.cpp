#include "Tweener.hpp"
#include "GameObject.hpp"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define M_FPI M_PI##f

using namespace DirectX;

std::vector<Tweener::TweenFunction> Tweener::_tweenFunctions;

// Create a new tweener
Tweener::Tweener( GameObject* gameObject )
    : Component( gameObject )
    , _tweenMethod( TweenMethod::Linear )
    , _tweenFunction( nullptr )
    , _duration( 1.0f )
    , _startTime( 0.0f )
    , _areValuesCompatible( false )
    , _isAffectingTransform( false )
{
    _isDrawable = false;
    _isEnabled = false;
    _usesLateUpdate = false;

    // Create the tween functions if they haven't been yet
    if ( _tweenFunctions.size() == 0 )
    {
        CreateTweenFunctions();
    }

    // Set the tween method and function in one go
    SetTweenMethod( TweenMethod::Linear );
}

// Destroy this tweener
Tweener::~Tweener()
{
    _tweenMethod   = TweenMethod::Linear; // 0
    _tweenFunction = nullptr;
    _duration      = 0.0f;
    _startTime     = 0.0f;
}

// Check if start, end, and target values are compatible.
void Tweener::CheckForCompatibleValues()
{
    _areValuesCompatible =  _targetValue
                         && ( _startValue.GetValueType() == _endValue.GetValueType() )
                         && ( _startValue.GetValueType() == _targetValue.GetTargetType() );
}

// Set start value
void Tweener::SetStartValue( TweenValue value )
{
    _startValue = value;
    CheckForCompatibleValues();
}

// Set ending value
void Tweener::SetEndValue( TweenValue value )
{
    _endValue = value;
    CheckForCompatibleValues();
}

// Set duration
void Tweener::SetDuration( float duration )
{
    _duration = duration;
}

// Set tween method
void Tweener::SetTweenMethod( TweenMethod method )
{
    if ( method == TweenMethod::TweenMethodCount )
    {
        method = TweenMethod::Linear;
    }

    _tweenMethod = method;
    _tweenFunction = _tweenFunctions[ static_cast<int>( method ) ];
}

// Starts the tweener
void Tweener::Start( const GameTime& gameTime, TweenTarget target, bool targetIsTransform )
{
    _startTime = gameTime.GetTotalTime();
    _targetValue = target;
    _isAffectingTransform = targetIsTransform;

    // Ensure the values are compatible and only start if they are
    CheckForCompatibleValues();
    SetEnabled( _areValuesCompatible );
}

// Update tween component
void Tweener::Update( const GameTime& gameTime )
{
    assert( _areValuesCompatible && "Tweener values are not compatible!" );

    // Get the time, and make sure it doesn't go higher than the duration
    float time = gameTime.GetTotalTime() - _startTime;
    if ( time >= _duration )
    {
        time = _duration;
        SetEnabled( false );
    }

    // Modify the target value
    if ( _tweenFunction && _targetValue )
    {
        switch ( _targetValue.GetTargetType() )
        {
            case TweenType::Float:
            {
                float src = _startValue.GetFloat();
                float dst = _endValue.GetFloat();
                
                float value = _tweenFunction( src, dst, time, _duration );
                _targetValue.SetValue( value );
                
                break;
            }
            case TweenType::Float2:
            {
                XMFLOAT2 src = _startValue.GetFloat2();
                XMFLOAT2 dst = _endValue.GetFloat2();
                
                XMFLOAT2 value;
                value.x = _tweenFunction( src.x, dst.x, time, _duration );
                value.y = _tweenFunction( src.y, dst.y, time, _duration );

                _targetValue.SetValue( value );
                break;
            }
            case TweenType::Float3:
            {
                XMFLOAT3 src = _startValue.GetFloat3();
                XMFLOAT3 dst = _endValue.GetFloat3();

                XMFLOAT3 value;
                value.x = _tweenFunction( src.x, dst.x, time, _duration );
                value.y = _tweenFunction( src.y, dst.y, time, _duration );
                value.z = _tweenFunction( src.z, dst.z, time, _duration );

                _targetValue.SetValue( value );
                break;
            }
            case TweenType::Float4:
            {
                XMFLOAT4 src = _startValue.GetFloat4();
                XMFLOAT4 dst = _endValue.GetFloat4();

                XMFLOAT4 value;
                value.x = _tweenFunction( src.x, dst.x, time, _duration );
                value.y = _tweenFunction( src.y, dst.y, time, _duration );
                value.z = _tweenFunction( src.z, dst.z, time, _duration );
                value.w = _tweenFunction( src.w, dst.w, time, _duration );

                _targetValue.SetValue( value );
                break;
            }
        }

        // If we're affecting the transform of our game object, we need to notify it that it has changed
        if ( _isAffectingTransform )
        {
            _gameObject->SetWorldMatrixDirty();
        }
    }
}