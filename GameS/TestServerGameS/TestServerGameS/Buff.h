


class Buff{
	int		type;
	int		level;
	float	time;
	bool	special;
public:
	Buff(int type, int level, float time, bool special = false);
	Buff();	

	void			SetType(int newType);
	void			SetLevel(int newLevel);
	void			SetTime(float newTime);
	void			SetSpecial(bool newSpecial);

	const int&		GetType() const;
	const float&	GetTime() const;
	const bool&		GetSpecial() const;
	const int&		GetLevel() const;

	void			SubTime(float deltaTime);
};