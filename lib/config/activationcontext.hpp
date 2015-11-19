/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2015 Icinga Development Team (http://www.icinga.org)    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef ACTIVATIONCONTEXT_H
#define ACTIVATIONCONTEXT_H

#include "config/i2-config.hpp"
#include "base/object.hpp"
#include <boost/thread/tss.hpp>
#include <stack>

namespace icinga
{

class I2_CONFIG_API ActivationContext : public Object
{
public:
	DECLARE_PTR_TYPEDEFS(ActivationContext);

	static ActivationContext::Ptr GetCurrentContext(void);

private:
	static void PushContext(const ActivationContext::Ptr& context);
	static void PopContext(void);

	static std::stack<ActivationContext::Ptr>& GetActivationStack(void);

	static boost::thread_specific_ptr<std::stack<ActivationContext::Ptr> > m_ActivationStack;

	friend class ActivationScope;
};

class I2_CONFIG_API ActivationScope
{
public:
	ActivationScope(const ActivationContext::Ptr& context = ActivationContext::Ptr());
	~ActivationScope(void);

	ActivationContext::Ptr GetContext(void) const;

private:
	ActivationContext::Ptr m_Context;
};

}

#endif /* ACTIVATIONCONTEXT_H */