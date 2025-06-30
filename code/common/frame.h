#ifndef __FRAME_H__
#define __FRAME_H__

#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "property_ids.h"

using PropertyNotification = std::function<void(PropertyID)>;

// 基础的Observable类，用于实现属性变化通知
class PropertyTrigger {
public:
	PropertyTrigger() noexcept = default;
	PropertyTrigger(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept = default;

	PropertyTrigger& operator=(const PropertyTrigger&) = delete;

	void clear_notifications() noexcept {
		m_vec_nf.clear();
	}

	uintptr_t add_notification(PropertyNotification&& pn);

	void remove_notification(uintptr_t cookie) noexcept {
		assert(cookie > 0 && cookie <= m_vec_nf.size());
		m_vec_nf[cookie - 1] = nullptr;
	}

protected:
	void PropertyTrigger::fire(uint32_t id);

private:
	std::vector<PropertyNotification> m_vec_nf;
};

// MVVM基础接口
class IViewModel : public PropertyTrigger {
public:
	virtual ~IViewModel() = default;
	virtual void update(float deltaTime) = 0;
};

class IView {
public:
	virtual ~IView() = default;
	virtual void render() = 0;
	virtual void bind_view_model(std::shared_ptr<IViewModel> vm) = 0;
};

class IModel : public PropertyTrigger {
public:
	virtual ~IModel() = default;
	virtual void update(float deltaTime) = 0;
};

#endif
