// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test.h"

class ExperimentStack : public Test
{
public:
	ExperimentStack()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));

			b2FixtureDef fd;
            fd.restitutionThreshold = 0.0f;
            fd.friction = 0.0f;
			fd.shape = &shape;

			ground->CreateFixture(&fd);
		}

		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f, 5.f);
            bd.bullet = true;
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;

			b2Vec2 vertices[8];
			vertices[0].Set(-1.f, -1.f);
			vertices[1].Set(0.f, -1.f);
			vertices[2].Set(1.f, -1.0f);
			vertices[3].Set(1.0f, 0.f);
			vertices[4].Set(1.0f, 1.0f);
			vertices[5].Set(0.f, 1.0f);
            vertices[6].Set(-1.f, 1.0f);
            vertices[7].Set(-1.f, 0.f);

			shape.Set(vertices, 8);

//			shape.SetAsBox(2.f, 2.f);

			b2FixtureDef fd;
			fd.shape = &shape;
            fd.restitutionThreshold = 0.0f;
            fd.restitution = 1.0f;
			fd.friction = 0.0f;
			fd.density = 1.0f;

			body->CreateFixture(&fd);
		}
	}

//	void Step(Settings& settings) override
//	{
//
//		Test::Step(settings);
//	}

	static Test* Create()
	{
		return new ExperimentStack;
	}

	b2Body* m_attachment;
	b2Body* m_platform;
	float m_speed;
};

static int testIndex = RegisterTest("Experiments", "Stack", ExperimentStack::Create);
