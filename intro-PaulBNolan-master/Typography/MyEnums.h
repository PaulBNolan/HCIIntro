#ifndef MY_ENUMS
#define MY_ENUMS

/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

/// <summary>
/// our animatiuons will go from appear to none to disappear
/// </summary>
enum class AnimationState
{
	None,
	Appear,
	Disappear
};


/// <summary>
/// different moide game can be 
/// starting with author then licience, producer, splash
/// </summary>
enum class GameState
{
	None,
	Author,
	Exit,
	Licence,
	Producer,
	Splash,
	Credits
};

#endif // !MY_ENUMS