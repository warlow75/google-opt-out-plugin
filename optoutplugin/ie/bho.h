// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <shlguid.h>
#include <exdispid.h>
#include <shlobj.h>
#include "opt_out.h"  // Generated by the MIDL compiler.
#include "resource.h"

DEFINE_GUID(CATID_AppContainerCompatible,
    0x59fb2056, 0xd625, 0x48d0, 0xa9, 0x44, 0x1a, 0x85, 0xb5, 0xab, 0x26, 0x40);

// Once loaded, this BHO ensures that the doubleclick cookie is persistently set
// to id=OPT_OUT, by resetting it every time a new page is loaded.
class ATL_NO_VTABLE CPersistentOptOutBHO
    : public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
      public ATL::CComCoClass<CPersistentOptOutBHO, &CLSID_PersistentOptOutBHO>,
      public ATL::IObjectWithSiteImpl<CPersistentOptOutBHO>,
      public ATL::IDispatchImpl<IPersistentOptOutBHO, &IID_IPersistentOptOutBHO,
                                &LIBID_PersistentOptOutLib, 1, 0>,
      public ATL::IDispEventImpl<1, CPersistentOptOutBHO,
                                 &DIID_DWebBrowserEvents2,
                                 &LIBID_SHDocVw, 1, 1> {
 public:
  CPersistentOptOutBHO() { }

  STDMETHOD(SetSite)(IUnknown *site);

  DECLARE_REGISTRY_RESOURCEID(IDR_PERSISTENTOPTOUTBHO)

  BEGIN_COM_MAP(CPersistentOptOutBHO)
    COM_INTERFACE_ENTRY(IPersistentOptOutBHO)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IObjectWithSite)
  END_COM_MAP()

  BEGIN_CATEGORY_MAP(CPersistentOptOutBHO)
    IMPLEMENTED_CATEGORY(CATID_AppContainerCompatible)
  END_CATEGORY_MAP()

  BEGIN_SINK_MAP(CPersistentOptOutBHO)
    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2,
                  DISPID_BEFORENAVIGATE2, BeforeNavigate)
  END_SINK_MAP()

  void STDMETHODCALLTYPE BeforeNavigate(IDispatch *disp,
                                        VARIANT *url,
                                        VARIANT *flags,
                                        VARIANT *target_frame_name,
                                        VARIANT *post_data,
                                        VARIANT *headers,
                                        VARIANT_BOOL *cancel);
 private:
  ATL::CComPtr<IWebBrowser2> web_browser_;
  bool advised_;
};

OBJECT_ENTRY_AUTO(__uuidof(PersistentOptOutBHO), CPersistentOptOutBHO)
