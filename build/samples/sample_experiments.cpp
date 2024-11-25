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
	explicit ExperimentStack( Settings& settings )
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
			bodyDef.type = b2_kinematicBody;
			bodyDef.position = b2Vec2{ 0.0f, -1.0f };
			b2BodyId groundId = b2CreateBody( m_worldId, &bodyDef );

			b2Polygon box = b2MakeBox( 100.0f, 1.0f );
			b2ShapeDef shapeDef = b2DefaultShapeDef();
			b2CreatePolygonShape( groundId, &shapeDef, &box );
		}

		
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.isBullet = true;
		bodyDef.enableSleep = false;

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.restitution = 1.0f;

		float h = 1.0f;
		b2Polygon box = b2MakeSquare( h );

		{
			bodyDef.position = b2Vec2{ 0, 1 };

			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}

		{
			bodyDef.position = b2Vec2{ 0, 3 };

			b2BodyId bodyId = b2CreateBody( m_worldId, &bodyDef );
			b2CreatePolygonShape( bodyId, &shapeDef, &box );
		}
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

		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.enableSleep = false;

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
			bodyDef.position = b2Vec2{ 0, 7 };

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



