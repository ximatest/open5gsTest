import * as schemas from './EditCfgSection';

export const bsfschema = {
  //title: "BSF Configuration",
  type: "object",
  properties: {
    bsf: {
      type: "object",
      title: "BSF",
      properties: {
        sbi: schemas.nf_sbi_Schema, 
        metrics: schemas.metricsSchema,
        relative_capacity: schemas.relative_capSchema,
      },
    },
    //nrf: schemas.nrfSchema,
    //parameter: schemas.paraSchema,
    //sbi: schemas.sbiSchema,
    logger: schemas.loggerSchema,
    cli: schemas.cliSchema,
  },
};

export const bsfuiSchema = {
  logger: schemas.loggerUiSchema,
  //sbi: schemas.sbiUiSchema,
  //nrf: schemas.nrfUiSchema,
  //parameter: schemas.paraUiSchema,
  bsf: {
    classNames: "col-xs-12",
    sbi: schemas.nf_sbi_UiSchema,
    metrics: schemas.metricsUiSchema,
    relative_capacity: schemas.relative_capUiSchema,
  },
  cli: schemas.cliUiSchema,
};