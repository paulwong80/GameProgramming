#include "Graphics.h"
#include <vector>
namespace RenderEngine {
	Mesh::Mesh(float radius, int step) : m_radius(radius), m_step(step)
	{
		pShader = std::make_unique<Shader>("Render/shaders/core.vs", "Render/shaders/core.fs");
		this->CreateCircle(radius, step);
	}
	void Mesh::Draw()
	{
		if (!border)
		{
			glEnable(GL_STENCIL_TEST);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glClear(GL_STENCIL_BUFFER_BIT);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
		}
		pShader->UseProgram();
		pShader->SetFloat("x",m_x);
		pShader->SetFloat("y", m_y);
		pShader->SetVec3("color", m_r, m_g, m_b);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, m_numOfVertices);
		if (!border)
		{
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			pShader->SetVec3("color", m_br, m_bg, m_bb);
			pShader->SetFloat("s", m_bscale);
			glDrawArrays(GL_TRIANGLE_FAN, 0, m_numOfVertices);
			glStencilMask(0xFF);
		}
		glBindVertexArray(0);
	}
	void Mesh::setPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}
	void Mesh::setSpeed(float x, float y)
	{
		m_sx = x;
		m_sy = y;
	}
	void Mesh::setScale(float s)
	{
		m_scale = s;
	}
	void Mesh::setColor(Color color)
	{
		m_r = color.R / 255.0f;
		m_b = color.G / 255.0f;
		m_g = color.B / 255.0f;
	}

	void Mesh::setBorderColor(Color color)
	{
		m_br = color.R / 255.0f;
		m_bb = color.G / 255.0f;
		m_bg = color.B / 255.0f;
	}

	void Mesh::setBorderThick(int t)
	{
		m_bscale = t / m_radius;
	}

	void Mesh::CreateCircle(float radius, int step) 
	{
		std::vector<float> points;
		points.push_back(0.0f);
		points.push_back(0.0f);
		points.push_back(0.0f);
		for (size_t i = 0; i < step; i++)
		{
			points.push_back(-sinf(2 * 3.1415f * i / step) * radius);
			points.push_back(cosf(2 * 3.1415f * i / step) * radius);
			points.push_back(0.0f);
		}
		points.push_back(0.0f);
		points.push_back(radius);
		points.push_back(0.0f);
		float* vertices = points.data();
		m_numOfVertices = points.size() / 3;
		this->CreateObject(vertices);
	}
	void Mesh::CreateObject(const float* vertices)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_numOfVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


}