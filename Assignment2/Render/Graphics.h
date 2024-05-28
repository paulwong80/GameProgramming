#pragma once

#include "Shader.h"
#include <memory.h>
#include <GL/glew.h>
#include "../Vec2.h"

struct Color
{
	int R, G, B;
};

namespace RenderEngine {

	class Mesh {
	public:
		Mesh(float radius, int step);
		void Draw();
		void setPosition(float x, float y);
		void setSpeed(float x, float y);
		void setScale(float s);
		void setColor(Color color);
		void setBorderColor(Color color);
		void setBorderThick(int t);
		void setRotation(float r);
		Vec2 getPosition();
	private:
		GLuint VAO, VBO, EBO;
		float m_radius;
		int m_step;
		float m_rotation = 0.0f;
		float m_x = 0.0f, m_y = 0.0f, m_sx = 0.0f, m_sy = 0.0f;
		float m_scale = 1.0f;
		float m_r=0.0f, m_g=0.0f, m_b=0.0f;
		bool border = true;
		float m_br , m_bg = 0.0f, m_bb = 0.0f;
		float m_bscale = 1.1f;
		unsigned int m_numOfVertices = 4;
		std::unique_ptr<Shader> pShader;
		void CreateCircle(float radius, int step);
		void CreateObject(const float* vertices);
	};
	

}


