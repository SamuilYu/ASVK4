#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>

#include "MyProtocolHandler.h"

extern "C"
{

SAL_DLLPUBLIC_EXPORT void* SAL_CALL component_getFactory(const char* pImplName      ,
                                                                void*     pServiceManager,
                                                                void*     pRegistryKey   )
{
    if ( !pServiceManager || !pImplName )
        return 0;

    css::uno::Reference< css::uno::XInterface > xFactory  ;
    ::rtl::OUString sImplName = ::rtl::OUString::createFromAscii(pImplName);

    if (sImplName == MYPROTOCOLHANDLER_IMPLEMENTATIONNAME)
    {
        css::uno::Sequence< ::rtl::OUString > lNames(1);
        lNames[0] = MYPROTOCOLHANDLER_SERVICENAME;
        xFactory = ::cppu::createSingleComponentFactory(MyProtocolHandler_createInstance, sImplName, lNames);
    }

    if (!xFactory.is())
        return 0;

    xFactory->acquire();
    return xFactory.get();
}

SAL_DLLPUBLIC_EXPORT void SAL_CALL component_getImplementationEnvironment(
    char const ** ppEnvTypeName, uno_Environment **)
{
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

} // extern C

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
