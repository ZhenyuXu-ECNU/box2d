// SPDX-FileCopyrightText: 2022 Erin Catto
// SPDX-License-Identifier: MIT

#include "benchmarks.h"
#include "draw.h"
#include "human.h"
#include "random.h"
#include "sample.h"
#include "settings.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>



class ExperimentStack : public Sample
{
public:

	int iter = 0;

	explicit ExperimentStack( Settings& settings )
		: Sample( settings )
	{
		b2World_SetGravity( m_worldId, b2Vec2{ 0.0f, -10.0f } );
		b2World_SetRestitutionThreshold( m_worldId, 0.0f );
		if ( settings.restart == false )
		{
			g_camera.m_center = { 0.0f, 50.0f };
			g_camera.m_zoom = 25.0f * 2.2f;
			settings.enableSleep = false;
		}

		{
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = b2_staticBody;
			bodyDef.position = b2Vec2{ 10.0f, -5.0f };
			b2BodyId groundId = b2CreateBody( m_worldId, &bodyDef );

			b2Polygon box = b2MakeBox( 100.0f, 1.0f );
			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeDef.friction = 0.0f;
			b2CreatePolygonShape( groundId, &shapeDef, &box );
		}

		
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.isBullet = false;
		bodyDef.enableSleep = false;
		
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.friction = 0.0f;
		shapeDef.restitution = 1.0f;

		float h = 1.0f;
		b2Polygon box = b2MakeSquare( h );

		{
			bodyDef.position = b2Vec2{ 5, -3 };

			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			id = bodyId;
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}

		/*{
			bodyDef.position = b2Vec2{ 0, 3 };

			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}*/
	}

	b2BodyId id;

	void Step( Settings& settings ) override
	{
		iter++;
		Sample::Step( settings );

		printf( "iteration: %d", iter );
		b2Vec2 lv  = b2Body_GetLinearVelocity( id );
		float av = b2Body_GetAngularVelocity( id );
		printf( "lv = %f %f, av = %f\n", lv.x, lv.y, av );
	}

	static Sample* Create( Settings& settings )
	{
		return new ExperimentStack( settings );
	}
};

static int experimentStack = RegisterSample( "Experiment", "Stack", ExperimentStack::Create );


class ExperimentHitGround : public Sample
{
public:
	explicit ExperimentHitGround( Settings& settings )
		: Sample( settings )
	{
		if ( settings.restart == false )
		{
			g_camera.m_center = { 0.0f, 50.0f };
			g_camera.m_zoom = 25.0f * 2.2f;
			settings.enableSleep = false;
		}

		{
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.position = b2Vec2{ 0.0f, -1.0f };
			b2BodyId groundId = b2CreateBody( m_worldId, &bodyDef );

			b2Polygon box = b2MakeBox( 100.0f, 1.0f );
			b2ShapeDef shapeDef = b2DefaultShapeDef();
			b2CreatePolygonShape( groundId, &shapeDef, &box );
		}

		b2World_SetGravity( m_worldId, b2Vec2{ 0, 0 } );


		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.enableSleep = false;
		bodyDef.isBullet = false;

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.restitution = 1.0f;

		float h = 1.0f;
		b2Polygon box = b2MakeSquare( h );

		//{
		//	bodyDef.position = b2Vec2{ 0, 1 };

		//	b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
		//	b2CreatePolygonShape( bodyId, &shapeDef, &box );
		//}

		{
			bodyDef.position = b2Vec2{ 0, 16 };
			bodyDef.linearVelocity = b2Vec2{ 0, -40 };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}
	}

	static Sample* Create( Settings& settings )
	{
		return new ExperimentHitGround( settings );
	}
};



static int experimentHitGround = RegisterSample( "Experiment", "Hit Ground", ExperimentHitGround::Create );


class ExperimentPropagation : public Sample
{
public:
	explicit ExperimentPropagation( Settings& settings )
		: Sample( settings )
	{
		if ( settings.restart == false )
		{
			g_camera.m_center = { 0.0f, 50.0f };
			g_camera.m_zoom = 25.0f * 2.2f;
			settings.enableSleep = false;
		}

		//{
		//	b2BodyDef bodyDef = b2DefaultBodyDef();
		//	bodyDef.position = b2Vec2{ 0.0f, -1.0f };
		//	b2BodyId groundId = b2CreateBody( m_worldId, &bodyDef );

		//	b2Polygon box = b2MakeBox( 100.0f, 1.0f );
		//	b2ShapeDef shapeDef = b2DefaultShapeDef();
		//	b2CreatePolygonShape( groundId, &shapeDef, &box );
		//}

		b2World_SetGravity( m_worldId, b2Vec2{ 0.0f, 0.0f } );
		b2World_SetRestitutionThreshold( m_worldId, 0.0f );

		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.enableSleep = false;
		bodyDef.isBullet = false;

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.restitution = 1.0f;

		float h = 1.0f;
		b2Polygon box = b2MakeSquare( h );

		{
			bodyDef.position = b2Vec2{ 2, 0 };
			bodyDef.linearVelocity = b2Vec2{ 0, 0 };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}

		{
			bodyDef.position = b2Vec2{ 4, 0 };
			bodyDef.linearVelocity = b2Vec2{ 0, 0 };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}

		{
			bodyDef.position = b2Vec2{ 6, 0 };
			bodyDef.linearVelocity = b2Vec2{ 0, 0 };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}

		{
			bodyDef.position = b2Vec2{ -2, 0 };
			bodyDef.linearVelocity = b2Vec2{ 2, 0 };
			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}
	}

	static Sample* Create( Settings& settings )
	{
		return new ExperimentPropagation( settings );
	}
};

static int experimentPropagation = RegisterSample( "Experiment", "box propagation", ExperimentPropagation::Create );



