//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FORM_H_INCLUDED
#define MK_FORM_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkRegistry.h>
#include <Object/Store/mkIndexStore.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkMake.h>
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkScheme.h>

#include <map>

namespace mk
{
	/* Form is the underlying data representation of the UI system
			- name, label and meta text
			- image address
			- ordering of the elements in a collection
	*/

	/*
		Types of forms :
			-Dropdown (one form is shown at a given time, with selection action)
			-Tabs (one form is shown at a given time)
	*/

	enum FormUpdate
	{
		FORM_DEFAULT = 0,
		FORM_ADDED = 1,
		FORM_REMOVED = 2,
		//FORM_DESTROYED = 3,
		FORM_UPDATED = 3
	};

    class MK_UI_EXPORT Form : public TypeObject, public Typed<Form>, public Updatable
    {
    public:
		typedef std::function<void(Form*)> Trigger;

	public:
		Form(const string& cls, const string& label = "", SchemeMapper containerMapper = nullptr, SchemeMapper elementMapper = nullptr);
		~Form();

		UiWindow* uiWindow();
		Form* parent() { return mParent; }
		Id index() const { return mIndex; }
		Widget* widget() { return mWidget; }
		bool container() { return mLabel == ""; }
		size_t updated() { return mUpdated; }
		size_t lastTick() { return mLastTick; }

		Scheme* scheme() { return &mScheme; }
		void setScheme(std::unique_ptr<Scheme> scheme);
		void setWidget(Widget* widget) { mWidget = widget; }

		const string& clas() const { return mCls; }
		const string& label() const { return mLabel; }
		const string& image() const { return this->getAttr("image"); }
		const string& name() const { return this->getAttr("name"); }
		const string& tooltip() const { return this->getAttr("tooltip"); }

		const string& fullIndex() const { return mFullIndex; }

		std::map<string, string>& attrs() { return mAttrs; }
		bool hasAttr(const string& name) { return mAttrs.find(name) != mAttrs.end(); }
		const string& getAttr(const string& name) const { if(mAttrs.find(name) != mAttrs.end()) return mAttrs.at(name); else return sNullString; }

		void setIndex(Id index);

		void setCls(const string& cls) { mCls = cls; }
		void setLabel(const string& label) { mLabel = label; mUpdated = mLastTick; }
		void setImage(const string& image) { mAttrs["image"] = image; }
		void setName(const string& name) { mAttrs["name"] = name; }
		void setTooltip(const string& tooltip) { mAttrs["tooltip"] = tooltip; }

		Registry<Form>* contents() { return &mContents; }

		void nextFrame(size_t tick, size_t delta);

		// Creation - removal
		void bind(Form* parent);

		void destroy();
		void flagDestroy();

		void clear();
		void flagClear();
		
		void remove(size_t index);

		Form* insert(std::unique_ptr<Form> form, size_t index);
		Form* append(std::unique_ptr<Form> form);
		std::unique_ptr<Form> release(size_t index);

		// Indexing
		string concatIndex();
		void updateIndex();

		void move(size_t from, size_t to);

		Form* prev();
		Form* next();
		size_t last();

		bool contains(Form* other);

		Form* findParent(const string& cls);

		// Specialization
		RootForm* rootForm();

		template <class T, class... Args>
		inline T* makeappend(Args&&... args)
		{
			return this->append(make<T>(std::forward<Args>(args)...))->as<T>();
		}

	public:
		Form* find(const string& search);

		//void added();
		//void removed();
		//void updated();
		//void altered();

		bool destroyed() { return mDestroy; }

	protected:
		Form* mParent;
		Id mIndex;
		string mFullIndex;
		string mCls;
		string mLabel;

		size_t mLastTick;
		size_t mUpdated;

		Scheme mScheme;

		Widget* mWidget;

		std::map<string, string> mAttrs;

		Index<Registry<Form>> mContents;

		bool mDestroy;

		static string sNullString;
    };


}

#endif // MK_FORM_H_INCLUDED
