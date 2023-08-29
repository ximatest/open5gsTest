import * as schemas from './EditCfgSection';

export const udrschema = {
  title: "UDR Configuration",
  type: "object",
  properties: {
    logger: schemas.loggerSchema,
    sbi: schemas.sbiSchema,
    nrf: schemas.nrfSchema,
    udr: {
      type: "object",
      title: "UDR",
      properties: {
        sbi: schemas.nf_sbi_Schema,  
      },
    },    
    
  },
};

export const udruiSchema = {
  logger: schemas.loggerUiSchema,
  sbi: schemas.sbiUiSchema,
  nrf: schemas.nrfUiSchema,
  udr: {
    classNames: "col-xs-12",
    sbi: schemas.nf_sbi_UiSchema,
  },
 
};