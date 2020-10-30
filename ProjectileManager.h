#pragma once

#define PROJECTILE_MAX 40



struct tagProjectile {
		string imgKey;
		float x, y;
		float angle;
		float speed;
		int width;
		int height;
		int frameX;
		int frameY;
		int damage;
		int count;
		int brassCount;
		bool isFrame;
		bool isStretch;
		bool isEnemyProjectTile;
		bool isAppear;
		bool isBrassing;
		bool isPingPong;

		RECT* _playerTargetRc;
		bool isFollowing;

};

class ProjectileManager{

private:
	tagProjectile _projectiles[PROJECTILE_MAX];

	string _strDamageBoundary = "����";
	string _followingAttack = "����";



public:
	
	void init();
	void release();
	void update();
	void render(HDC hdc);
	void CreateProjectile(string imgKey, int x, int y, int damage = 10, float angle = 0.0f,
		float speed = 0.5f, int size = 20, bool isEnemy = false, bool isFrame = false, bool isStretch = false);

	void CreateProjectile(string imgKey, int x, int y, int damage = 1, int width = 100, int height = 20, bool isLeft = false);

	void CreateProjectile(int x, int y, int damage, int width, int height);

	void CreateProjectile(string imgKey, RECT* playerTargetRc, int x, int y, int damage = 10, float angle = 0.0f, float speed = 0.5f, int size = 20, bool isEnemy = false, bool isFrame = true, bool isFollowing = true);
	tagProjectile* GetProjectile() { return _projectiles; }

	float shootToTarget(int index);
};

